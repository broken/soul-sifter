//
//  RapidEvolutionMusicDatabaseWriter.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionMusicDatabaseWriter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <xercesc/framework/XMLFormatter.hpp>

#include "DTXMLWriter.h"
#include "Mix.h"
#include "REAlbumCover.h"
#include "RESetting.h"
#include "RESong.h"
#include "REXml.h"
#include "Style.h"

using namespace std;
using namespace xercesc;

typedef pair<string,string> attrib;

namespace {
    
    string int2str(int num) {
        ostringstream oss;
        oss << num;
        return oss.str();
    }
    
    void deleteAttribs(attrib* attribs[]) {
        for (int i = 0; attribs[i] != NULL; ++i) {
            delete attribs[i];
        }
    }
    
}

namespace soulsifter {

# pragma mark initialization

RapidEvolutionMusicDatabaseWriter::RapidEvolutionMusicDatabaseWriter() :
processing(false) {
}

# pragma mark xml reader

void RapidEvolutionMusicDatabaseWriter::write() {
    cout << "RapidEvolutionMusicDatabaseWriter.write" << endl;
    
    XMLPlatformUtils::Initialize();
    DTXMLWriter w("UTF-8", "/Users/rneale/music_database.xml.out");
    
    w.startDocument();
    attrib* dbAttribs[] = { new attrib("version","1.04"), NULL };
    w.startElement("music_database", dbAttribs).endl();
    deleteAttribs(dbAttribs);
    w.startElement("config", NULL).endl();
    
    w.startElement("settings", NULL).endl();
    vector<const RESetting*> settings;
    RESetting::findAll(&settings);
    for (vector<const RESetting*>::iterator it = settings.begin(); it != settings.end(); ++it) {
        if ((*it)->getValue().length() > 0) {
            w.startElement((*it)->getName(), NULL);
            w.writeChars((*it)->getValue());
            w.endElement((*it)->getName());
        } else {
            w.startElement((*it)->getName(), NULL, true).endl();
        }
    }
    //f << "</settings>" << endl;
    w.endElement("settings");
    
    // XML in these contains the newline at the end
    w.writeChars(REXml::findByName("columns")->getXml(), false);
    w.writeChars(REXml::findByName("tables")->getXml(), false);
    w.writeChars(REXml::findByName("user")->getXml(), false);
    
    w.endElement("config");
    
    const vector<Style*>* styles;
    const vector<Style*>* children;
    const vector<Style*>* parents;
    Style::findAll(&styles);
    //f << "<styles dirty=\"no\" num_styles=\"" << styles->size() << "\">" << endl;
    attrib* styleAttribs[] = { new attrib("dirty","no"), new attrib("num_styles", int2str((int)styles->size())), NULL };
    w.startElement("styles", styleAttribs).endl();
    deleteAttribs(styleAttribs);
    for (vector<Style*>::const_iterator it = styles->begin(); it != styles->end(); ++it) {
        // get child ids
        ostringstream osschild;
        children = &(*it)->getChildren();
        bool first = true;
        for (vector<Style*>::const_iterator jt = children->begin(); jt != children->end(); ++jt) {
            if (!first) osschild << ",";
            osschild << (*jt)->getREId();
            first = false;
        }
        // get parent ids
        ostringstream ossparent;
        parents = &(*it)->getParents();
        first = true;
        for (vector<Style*>::const_iterator jt = parents->begin(); jt != parents->end(); ++jt) {
            if (!first) ossparent << ",";
            ossparent << (*jt)->getREId();
            first = false;
        }
        if (first) ossparent << "-1";
        // now create style element
        attrib* styleAttribs[] = {
            new attrib("category_only","no"),
            new attrib("child_ids",osschild.str()),
            new attrib("description", ""),
            new attrib("id", int2str((*it)->getREId())),
            new attrib("name",(*it)->getREName()),
            new attrib("parent_ids",ossparent.str()),
            NULL
        };
        w.startElement("style", styleAttribs, true).endl();
        deleteAttribs(styleAttribs);
        /*w.startElement("include", NULL).endl();
        w.startElement("songs", NULL).endl();
        vector<Song*>* songs = NULL;
        Song::findSongsByStyle((**it), &songs);
        for (vector<Song*>::iterator it = songs->begin(); it != songs->end(); ++it) {
            w.startElement("song", NULL).writeInt((*it)->getRESongId()).endElement("song");
            delete(*it);
        }*/
    }
    //f << "</styles>" << endl;
    w.endElement("styles");
    
    attrib* songsAttribs[] = {
        new attrib("check_unique_id","no"),
        new attrib("max_unique_id",int2str(RESong::maxREId() + 1)),
        NULL
    };
    w.startElement("songs", songsAttribs).endl();
    deleteAttribs(songsAttribs);
    RESong::RESongIterator* songs = RESong::findAll();
    RESong song;
    while (songs->next(&song)) {
        attrib* songAttribs[] = {
            new attrib("num_excludes","0"),
            new attrib("num_mixouts",int2str(songs->getMixoutCountForCurrentSong())),
            NULL
        };
        w.startElement("song", songAttribs).endl();
        deleteAttribs(songAttribs);
        //f << "<unique_id>" << song.getUniqueId() << "</unique_id>" << endl;
        w.startElement("unique_id", NULL).writeInt(song.getId()).endElement("unique_id");
        //f << "<songid_winfo>" << song.getSongIdWInfo() << "</songid_winfo>" << endl;
        w.startElement("songid_winfo", NULL).writeChars(song.getSongidWinfo())->endElement("songid_winfo");
        //f << "<songid>" << song.getSongId() << "</songid>" << endl;
        w.startElement("songid", NULL).writeChars(song.getSongid())->endElement("songid");
        //f << "<shortid>" << song.getShortId() << "</shortid>" << endl;
        w.startElement("shortid", NULL).writeChars(song.getShortid())->endElement("shortid");
        //f << "<shortid_winfo>" << song.getShortIdWInfo() << "</shortid_winfo>" << endl;
        w.startElement("shortid_winfo", NULL).writeChars(song.getShortidWinfo())->endElement("shortid_winfo");
        if (song.getArtist().length() > 0)
            //f << "<artist>" << song.getArtist() << "</artist>" << endl;
            w.startElement("artist", NULL).writeChars(song.getArtist())->endElement("artist");
        if (song.getAlbum().length() > 0)
            //f << "<album>" << song.getAlbum() << "</album>" << endl;
            w.startElement("album", NULL).writeChars(song.getAlbum())->endElement("album");
        if (song.getTrack().length() > 0)
            //f << "<track>" << song.getTrack() << "</track>" << endl;
            w.startElement("track", NULL).writeChars(song.getTrack())->endElement("track");
        if (song.getTitle().length() > 0)
            //f << "<title>" << song.getTitle() << "</title>" << endl;
            w.startElement("title", NULL).writeChars(song.getTitle())->endElement("title");
        if (song.getRemix().length() > 0)
            //f << "<remix>" << song.getRemix() << "</remix>" << endl;
            w.startElement("remix", NULL).writeChars(song.getRemix())->endElement("remix");
        if (song.getComments().length() > 0)
            //f << "<comments>" << song.getComments() << "</comments>" << endl;
            w.startElement("comments", NULL).writeChars(song.getComments())->endElement("comments");
        if (song.getFeaturing().length() > 0)
            //f << "<custom1>" << song.getFeaturing() << "</custom1>" << endl;
            w.startElement("custom1", NULL).writeChars(song.getFeaturing())->endElement("custom1");
        if (song.getReleaseDate().length() > 0)
            //f << "<custom2>" << song.getReleaseDate() << "</custom2>" << endl;
            w.startElement("custom2", NULL).writeChars(song.getReleaseDate())->endElement("custom2");
        if (song.getLabel().length() > 0)
            //f << "<custom3>" << song.getLabel() << "</custom3>" << endl;
            w.startElement("custom3", NULL).writeChars(song.getLabel())->endElement("custom3");
        if (song.getCatalogId().length() > 0)
            //f << "<custom4>" << song.getCatalogId() << "</custom4>" << endl;
            w.startElement("custom4", NULL).writeChars(song.getCatalogId())->endElement("custom4");
        if (song.getTime().length() > 0)
            //f << "<time>" << song.getTime() << "</time>" << endl;
            w.startElement("time", NULL).writeChars(song.getTime())->endElement("time");
        if (song.getTimeSignature().length() > 0)
            //f << "<time_signature>" << song.getTimeSignature() << "</time_signature>" << endl;
            w.startElement("time_signature", NULL).writeChars(song.getTimeSignature())->endElement("time_signature");
        if (song.getFilename().length() > 0)
            //f << "<filename>" << song.getFilename() << "</filename>" << endl;
            w.startElement("filename", NULL).writeChars(song.getFilename())->endElement("filename");
        if (song.getDigitalOnly().length() > 0)
            //f << "<digital_only>" << song.getDigitalOnly() << "</digital_only>" << endl;
            w.startElement("digital_only", NULL).writeChars(song.getDigitalOnly())->endElement("digital_only");
        if (song.getDisabled().length() > 0)
            //f << "<disabled>" << song.getDisabled() << "</disabled>" << endl;
            w.startElement("disabled", NULL).writeChars(song.getDisabled())->endElement("disabled");
        if (song.getCompilation().length() > 0)
            //f << "<compilation>" << song.getCompilation() << "</compilation>" << endl;
            w.startElement("compilation", NULL).writeChars(song.getCompilation())->endElement("compilation");
        if (song.getKeyStart().length() > 0)
            //f << "<key_start>" << song.getKeyStart() << "</key_start>" << endl;
            w.startElement("key_start", NULL).writeChars(song.getKeyStart())->endElement("key_start");
        if (song.getKeyEnd().length() > 0)
            //f << "<key_end>" << song.getKeyEnd() << "</key_end>" << endl;
            w.startElement("key_end", NULL).writeChars(song.getKeyEnd())->endElement("key_end");
        if (song.getKeyAccuracy() > 0)
            //f << "<key_accuracy>" << song.getKeyAccuracy() << "</key_accuracy>" << endl;
            w.startElement("key_accuracy", NULL).writeInt(song.getKeyAccuracy()).endElement("key_accuracy");
        if (song.getBpmStart().length() > 0)
            //f << "<bpm_start>" << song.getBPMStart() << "</bpm_start>" << endl;
            w.startElement("bpm_start", NULL).writeStr(song.getBpmStart()).endElement("bpm_start");
        if (song.getBpmEnd().length() > 0)
            //f << "<bpm_end>" << song.getBPMEnd() << "</bpm_end>" << endl;
            w.startElement("bpm_end", NULL).writeStr(song.getBpmEnd()).endElement("bpm_end");
        if (song.getBpmAccuracy() > 0)
            //f << "<bpm_accuracy>" << song.getBPMAccuracy() << "</bpm_accuracy>" << endl;
            w.startElement("bpm_accuracy", NULL).writeInt(song.getBpmAccuracy()).endElement("bpm_accuracy");
        if (song.getBeatIntensity() > 0)
            //f << "<beat_intensity>" << song.getBeatIntensity() << "</beat_intensity>" << endl;
            w.startElement("beat_intensity", NULL).writeInt(song.getBeatIntensity()).endElement("beat_intensity");
        if (song.getReplayGain().length() > 0)
            //f << "<replay_gain>" << song.getReplayGain() << "</replay_gain>" << endl;
            w.startElement("replay_gain", NULL).writeStr(song.getReplayGain()).endElement("replay_gain");
        if (song.getNumPlays() > 0)
            //f << "<num_plays>" << song.getNumPlays() << "</num_plays>" << endl;
            w.startElement("num_plays", NULL).writeInt(song.getNumPlays()).endElement("num_plays");
        if (song.getRating() > 0)
            //f << "<rating>" << song.getRating() << "</rating>" << endl;
            w.startElement("rating", NULL).writeInt(song.getRating()).endElement("rating");
        if (song.getDateAdded().length() > 0)
            //f << "<date_added>" << song.getDateAdded() << "</date_added>" << endl;
            w.startElement("date_added", NULL).writeChars(song.getDateAdded())->endElement("date_added");
        if (song.getStylesBitmask().length() > 0)
            //f << "<styles_bitmask>" << song.getStylesBitmask() << "</styles_bitmask>" << endl;
            w.startElement("styles_bitmask", NULL).writeChars(song.getStylesBitmask())->endElement("styles_bitmask");
        //f << "</song>" << endl;
        w.endElement("song");
    }
    delete songs;
    //f << "</songs>" << endl;
    w.endElement("songs");
    
    // TODO mixouts
    //f << "<mixouts>" << endl;
    w.startElement("mixouts", NULL).writeNewline();
    Mix::MixResultSet* mixes = Mix::findAll();
    Mix mix;
    while (mixes->next(&mix)) {
        //f << "<mixout>" << endl;
        w.startElement("mixout", NULL).writeNewline();
        //f << "<from_unique_id>" << mix.getOutSong()->getRESongId() << "</from_unique_id>" << endl;
        w.startElement("from_unique_id", NULL).writeInt(mix.getOutSong()->getRESongId()).endElement("from_unique_id");
        //f << "<to_unique_id>" << mix.getInSong()->getRESongId() << "</to_unique_id>" << endl;
        w.startElement("to_unique_id", NULL).writeInt(mix.getInSong()->getRESongId()).endElement("to_unique_id");
        w.startElement("bpm_diff", NULL).writeStr(mix.getBpmDiff()).endElement("bpm_diff");
        if (mix.getRank() > 0)
            //f << "<rank>" << mix.getRank() << "</rank>" << endl;
            w.startElement("rank", NULL).writeInt(mix.getRank()).endElement("rank");
        if (mix.getComments().length() > 0)
            //f << "<comments>" << mix.getComments() << "</comments>" << endl;
            w.startElement("comments", NULL).writeChars(mix.getComments())->endElement("comments");
        if (mix.getAddon())
            //f << "<addon>yes</addon>" << endl;
            w.startElement("addon", NULL).writeBoolAsYesOrNo(mix.getAddon()).endElement("addon");
        //f << "</mixout>" << endl;
        w.endElement("mixout");
    }
    //f << "</mixouts>" << endl;
    w.endElement("mixouts");
    
    //f << "<excludes/>" << endl;
    w.startElement("excludes", NULL, true).endl();
    
    // TODO artists?
    //f << "<artists/>" << endl;
    w.startElement("artists", NULL, true).endl();
    
    //f << "<albumcovers>" << endl;
    w.startElement("albumcovers", NULL).writeNewline();
    REAlbumCover::REAlbumCoverIterator* covers = REAlbumCover::findAll();
    REAlbumCover ac;
    while (covers->next(&ac)) {
        attrib* acAttribs[] = {
            new attrib("id", ac.getREId()),
            new attrib("thumbnail",ac.getThumbnail()),
            NULL
        };
        w.startElement("albumcover", acAttribs).endl();
        deleteAttribs(acAttribs);
        attrib* imgAttribs[] = { new attrib("filename", ac.getThumbnail()), NULL };
        w.startElement("image", imgAttribs, true).endl();
        deleteAttribs(imgAttribs);
        w.endElement("albumcover");
    }
    delete covers;
    //f << "</albumcovers>" << endl;
    w.endElement("albumcovers");
    
    //f << "</music_database>" << endl;*/
    w.endElement("music_database");
    w.endDocument();
}

}
