//
//  Search.cpp
//  soul-sifter
//
//  Created by Robby Neale on 7/7/14.
//
//

#include "Search.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string.hpp>

#include "MysqlAccess.h"
#include "soul_sifter.pb.h"
#include "soul_sifter_service.pb.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

namespace {

struct CamelotKeys {
  static boost::unordered_map<string, string> init() {
    boost::unordered_map<string, string> camelotKeys;
    camelotKeys["1A"] = "Ab minor";
    camelotKeys["1B"] = "B major";
    camelotKeys["2A"] = "Eb minor";
    camelotKeys["2B"] = "F# major";
    camelotKeys["3A"] = "Bb minor";
    camelotKeys["3B"] = "Db major";
    camelotKeys["4A"] = "F minor";
    camelotKeys["4B"] = "Ab major";
    camelotKeys["5A"] = "C minor";
    camelotKeys["5B"] = "Eb major";
    camelotKeys["6A"] = "G minor";
    camelotKeys["6B"] = "Bb major";
    camelotKeys["7A"] = "D minor";
    camelotKeys["7B"] = "F major";
    camelotKeys["8A"] = "A minor";
    camelotKeys["8B"] = "C major";
    camelotKeys["9A"] = "E minor";
    camelotKeys["9B"] = "G major";
    camelotKeys["10A"] = "B minor";
    camelotKeys["10B"] = "D major";
    camelotKeys["11A"] = "F# minor";
    camelotKeys["11B"] = "A major";
    camelotKeys["12A"] = "Db minor";
    camelotKeys["12B"] = "E major";
    return camelotKeys;
  }
  static const boost::unordered_map<string, string> map;
};

const boost::unordered_map<string, string> CamelotKeys::map = CamelotKeys::init();

struct Atom {
  enum Type {
    ANY,
    S_ID,
    S_ARTIST,
    S_TITLE,
    S_REMIXER,
    S_RATING,
    S_COMMENT,
    S_TRASHED,
    S_LOW_QUALITY,
    A_ID,
    A_NAME,
    A_ARTIST,
    A_MIXED,
    A_LABEL,
    A_YEAR,
  };
  enum Property {
    NONE = 0x00,
    NEGATED = 0x01,
    CASE_SENSITIVE = 0x02,
  };
  string value;
  Type type;
  int props;
  
  void clear() {
    value = "";
    type = ANY;
    props = NONE;
  }
};

void splitString(const string& query, vector<string>* atoms) {
  boost::tokenizer<boost::escaped_list_separator<char> > tokenizer(query, boost::escaped_list_separator<char>('\\', ' ', '\"'));
  for (boost::tokenizer<boost::escaped_list_separator<char> >::iterator it = tokenizer.begin(); it != tokenizer.end(); ++it) {
    atoms->push_back(*it);
  }
}

bool parse(const string& queryFragment, Atom* atom) {
  atom->clear();
  boost::regex regex("^(-)?((id|a|artist|t|title|r|remixer|rating|comment|trashed|lowq|aid|n|album|m|mixed|l|label|y|year):)?(.+)$");
  boost::smatch match;
  if (!boost::regex_match(queryFragment, match, regex)) {
    return false;
  }
  if (match[1].length() > 0) {
    atom->props |= Atom::NEGATED;
  }
  if (match[2].length() > 0) {
    if (!match[3].compare("id")) {
      atom->type = Atom::S_ID;
    } else if (!match[3].compare("a") || !match[3].compare("artist")) {
      atom->type = Atom::S_ARTIST;
    } else if (!match[3].compare("t") || !match[3].compare("title")) {
      atom->type = Atom::S_TITLE;
    } else if (!match[3].compare("r") || !match[3].compare("remixer")) {
      atom->type = Atom::S_REMIXER;
    } else if (!match[3].compare("rating")) {
      atom->type = Atom::S_RATING;
    } else if (!match[3].compare("comment")) {
      atom->type = Atom::S_COMMENT;
    } else if (!match[3].compare("trashed")) {
      atom->type = Atom::S_TRASHED;
    } else if (!match[3].compare("lowq")) {
      atom->type = Atom::S_LOW_QUALITY;
    } else if (!match[3].compare("aid")) {
      atom->type = Atom::A_ID;
    } else if (!match[3].compare("n") || !match[3].compare("album")) {
      atom->type = Atom::A_NAME;
    } else if (!match[3].compare("m") || !match[3].compare("mixed")) {
      atom->type = Atom::A_MIXED;
    } else if (!match[3].compare("l") || !match[3].compare("label")) {
      atom->type = Atom::A_LABEL;
    } else if (!match[3].compare("y") || !match[3].compare("year")) {
      atom->type = Atom::A_YEAR;
    } else {
      // error
      return false;
    }
  }
  boost::regex quoteRegex("'");
  atom->value = boost::regex_replace(string(match[4]), quoteRegex, "\\\\'");
  return true;
}

string buildQueryPredicate(const vector<Atom>& atoms) {
  stringstream ss;
  for (Atom atom : atoms) {
    ss << " and ";
    if (atom.props & Atom::NEGATED) {
      ss << "not ";
    }
    if (atom.type == Atom::ANY) {
      ss << "(s.artist like '%" << atom.value << "%' or s.title like '%" << atom.value << "%' or s.remixer like '%" << atom.value << "%' or s.comment like '%" << atom.value << "%' or a.name like '%" << atom.value << "%')";
    } else if (atom.type == Atom::S_ID) {
      ss << "s.id = " << atom.value;
    } else if (atom.type == Atom::S_ARTIST) {
      ss << "s.artist like '%" << atom.value << "%'";
    } else if (atom.type == Atom::S_TITLE) {
      ss << "s.title like '%" << atom.value << "%'";
    } else if (atom.type == Atom::S_REMIXER) {
      ss << "s.remixer like '%" << atom.value << "%'";
    } else if (atom.type == Atom::S_RATING) {
      ss << "s.rating >= " << atom.value;
    } else if (atom.type == Atom::S_COMMENT) {
      ss << "s.comment like '%" << atom.value << "%'";
    } else if (atom.type == Atom::S_TRASHED) {
      ss << "s.trashed = " << atom.value;
    } else if (atom.type == Atom::S_LOW_QUALITY) {
      ss << "s.lowQuality = " << atom.value;
    } else if (atom.type == Atom::A_ID) {
      ss << "a.id = " << atom.value;
    } else if (atom.type == Atom::A_NAME) {
      ss << "a.name like '%" << atom.value << "%'";
    } else if (atom.type == Atom::A_MIXED) {
      ss << "a.mixed = " << atom.value;
    } else if (atom.type == Atom::A_LABEL) {
      ss << "a.label like '%" << atom.value << "%'";
    } else if (atom.type == Atom::A_YEAR) {
      ss << "a.year = " << atom.value;
    }
  }
  return ss.str();
}

string buildOptionPredicate(const proto::FindSongsRequest& request) {
  stringstream ss;
  if (request.has_key_to_match()) {
    // assume key lock always on for now
    ss << " and (";
    int num = 0;
    switch (request.key_to_match()) {
      case 17: // Gsm = 1A
      case 5:  // B = 1B
        ss << "find_in_set('" << CamelotKeys::map.at("12A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("12B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 18: // Ebm = 2A
      case 6:  // Fs = 2B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("1A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("1B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 19: // Bbm = 3A
      case 7:  // Db = 3B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("2A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("2B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 20: // Fm = 4A
      case 8:  // Ab = 4B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("3A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("3B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 21: // Cm = 5A
      case 9:  // Eb = 5B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("4A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("4B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 22: // Gm = 6A
      case 10: // Bb = 6B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("5A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("5B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 23: // Dm = 7A
      case 11: // F = 7B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("6A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("6B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 12: // Am = 8A
      case 0:  // C = 8B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("7A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("7B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 13: // Em = 9A
      case 1:  // G = 9B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("8A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("8B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 14: // Bm = 10A
      case 2:  // D = 10B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("9A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("9B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 15: // Fsm = 11A
      case 3:  // A = 11B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("10A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("10B") << "', tonicKeys)>0";
        if (++num == 3) break;
      case 16: // Csm = 12A
      case 4:  // E = 12B
        if (num != 0) ss << " or ";
        ss << "find_in_set('" << CamelotKeys::map.at("11A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("11B") << "', tonicKeys)>0";
        if (++num == 3) break;
        ss << " or find_in_set('" << CamelotKeys::map.at("12A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("12B") << "', tonicKeys)>0";
        if (++num == 3) break;
        ss << " or find_in_set('" << CamelotKeys::map.at("1A") << "', tonicKeys)>0 or find_in_set('" << CamelotKeys::map.at("1B") << "', tonicKeys)>0";
        if (++num == 3) break;
      default:
        cout << "Error. Unable to find key." << endl;
        return "";
    }
    ss << ")";
  }
  if (request.has_max_bpm() && request.has_min_bpm()) {
    ss << " and (bpm between " << request.min_bpm() << " and " << request.max_bpm();
    ss << " or bpm between " << request.min_bpm() / 2 << " and " << request.max_bpm() / 2;
    ss << " or bpm between " << request.min_bpm() * 2 << " and " << request.max_bpm() * 2 << ")";
  }
  if (request.genre_size() > 0) {
    ss << " and s.styleId in (";
    google::protobuf::RepeatedPtrField<proto::Genre> genres = request.genre();
    string separator("");
    for (google::protobuf::RepeatedPtrField<proto::Genre>::const_iterator it = genres.begin(); it != genres.end(); ++it) {
      ss << separator << it->id();
      separator = ",";
    }
    ss << ")";
  }
  return ss.str();
}
  
}  // anon namespace

void searchSongs(const proto::FindSongsRequest& request, proto::FindSongsResponse* response) {
  vector<string> fragments;
  splitString(request.query(), &fragments);
  
  vector<Atom> atoms;
  for (string fragment : fragments) {
    Atom atom;
    parse(fragment, &atom);
    atoms.push_back(atom);
  }
  
  stringstream ss;
  ss << "select s.id, s.artist, s.track, s.title, s.remixer, s.featuring, s.filePath, s.rating, s.dateAdded, s.bpm, s.comments, s.trashed, s.lowQuality, s.albumId, s.albumPartId, s.tonicKeys, a.id, a.artist, a.name, a.coverFilepath, a.mixed, a.label, a.catalogId, a.releaseDateYear, a.releaseDateMonth, a.releaseDateDay from Songs s inner join Albums a on s.albumid = a.id where true";
  ss << buildQueryPredicate(atoms);
  ss << buildOptionPredicate(request);
  
  cout << "Query:" << endl << ss.str() << endl;
  
  try {
    sql::Statement *stmt = MysqlAccess::getInstance().getConnection()->createStatement();
    sql::ResultSet *rs = stmt->executeQuery(ss.str());
    while (rs->next()) {
      proto::Song *song = response->add_song();
      song->set_id(rs->getInt(1));
      song->set_artist(rs->getString(2));
      song->set_track(rs->getString(3));
      song->set_title(rs->getString(4));
      song->set_remixer(rs->getString(5));
      song->set_featuring(rs->getString(6));
      song->set_filepath(rs->getString(7));
      song->set_rating(rs->getInt(8));
      song->set_dateadded(rs->getString(9));
      song->set_bpm(rs->getString(10));
      song->set_comments(rs->getString(11));
      song->set_trashed(rs->getBoolean(12));
      song->set_lowquality(rs->getBoolean(13));
      // song->setRESongId(rs->getInt("s.reSongId"));
      song->set_albumid(rs->getInt(14));
      if (!rs->isNull(15)) song->set_albumpartid(rs->getInt(15));
      // keys
      if (!rs->isNull(16)) {
        string dbSet = rs->getString(16);
        set<string> keys;
        boost::split(keys, dbSet, boost::is_any_of(","));
        boost::regex keyRegex("^([a-fA-F])(#)?(b)? (major)?(minor)?$");
        for (string key : keys) {
          // std::replace(key.begin(), key.end(), '#', 's');
          boost::smatch match;
          if (!boost::regex_match(key, match, keyRegex)) {
            cout << "WTF" << endl << key << " did not match regex" << endl;
          } else {
            stringstream ss;
            ss << match[1];
            if (match[2].length() > 0) ss << 's';
            ss << match[3];
            if (match[5].length() > 0) ss << 'm';
            // TODO proto::Song_TonicKey tonicKey = proto::Song_TonicKey.
          }
        }
      }
      // album
      proto::Album *album = song->mutable_album();
      album->set_id(rs->getInt(17));
      album->set_artist(rs->getString(18));
      album->set_name(rs->getString(19));
      album->set_coverfilepath(rs->getString(20));
      album->set_mixed(rs->getBoolean(21));
      album->set_label(rs->getString(22));
      album->set_catalogid(rs->getString(23));
      album->set_releasedateyear(rs->getInt(24));
      album->set_releasedatemonth(rs->getInt(25));
      album->set_releasedateday(rs->getInt(26));
      // genres
      sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select styleId from SongStyles where songId = ?");
      ps->setInt(1, song->id());
      sql::ResultSet *rsg = ps->executeQuery();
      while (rsg->next()) {
        proto::Genre *genre = song->add_genre();
        genre->set_id(rsg->getInt(1));
      }
      rsg->close();
      delete rsg;
    }
    rs->close();
    delete rs;
    delete stmt;
  } catch (sql::SQLException &e) {
    cerr << "ERROR: SQLException in " << __FILE__;
    cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
    cerr << "ERROR: " << e.what();
    cerr << " (MySQL error code: " << e.getErrorCode();
    cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
    exit(1);
  }
}
  
}  // namespace soulsifter
}  // namespace dogatech