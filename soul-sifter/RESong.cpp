//
//  RESong.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "RESong.h"

#include <cmath>
#include <string>

#include <boost/regex.hpp>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"
#include "DTVectorUtil.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    RESong::RESong() :
    id(0),
    songidWinfo(),
    songid(),
    shortid(),
    shortidWinfo(),
    artist(),
    album(),
    track(),
    title(),
    time(),
    timeSignature(),
    filename(),
    digitalOnly(),
    compilation(),
    keyStart(),
    keyAccuracy(0),
    bpmStart(),
    bpmAccuracy(0),
    rating(0),
    dateAdded(),
    catalogId(),
    label(),
    remix(),
    numPlays(0),
    comments(),
    releaseDate(),
    featuring(),
    keyEnd(),
    disabled(),
    bpmEnd(),
    beatIntensity(0),
    replayGain(),
    stylesBitmask() {
    }

    RESong::RESong(const RESong& reSong) :
    id(reSong.getId()),
    songidWinfo(reSong.getSongidWinfo()),
    songid(reSong.getSongid()),
    shortid(reSong.getShortid()),
    shortidWinfo(reSong.getShortidWinfo()),
    artist(reSong.getArtist()),
    album(reSong.getAlbum()),
    track(reSong.getTrack()),
    title(reSong.getTitle()),
    time(reSong.getTime()),
    timeSignature(reSong.getTimeSignature()),
    filename(reSong.getFilename()),
    digitalOnly(reSong.getDigitalOnly()),
    compilation(reSong.getCompilation()),
    keyStart(reSong.getKeyStart()),
    keyAccuracy(reSong.getKeyAccuracy()),
    bpmStart(reSong.getBpmStart()),
    bpmAccuracy(reSong.getBpmAccuracy()),
    rating(reSong.getRating()),
    dateAdded(reSong.getDateAdded()),
    catalogId(reSong.getCatalogId()),
    label(reSong.getLabel()),
    remix(reSong.getRemix()),
    numPlays(reSong.getNumPlays()),
    comments(reSong.getComments()),
    releaseDate(reSong.getReleaseDate()),
    featuring(reSong.getFeaturing()),
    keyEnd(reSong.getKeyEnd()),
    disabled(reSong.getDisabled()),
    bpmEnd(reSong.getBpmEnd()),
    beatIntensity(reSong.getBeatIntensity()),
    replayGain(reSong.getReplayGain()),
    stylesBitmask(reSong.getStylesBitmask()) {
    }

    void RESong::operator=(const RESong& reSong) {
        id = reSong.getId();
        songidWinfo = reSong.getSongidWinfo();
        songid = reSong.getSongid();
        shortid = reSong.getShortid();
        shortidWinfo = reSong.getShortidWinfo();
        artist = reSong.getArtist();
        album = reSong.getAlbum();
        track = reSong.getTrack();
        title = reSong.getTitle();
        time = reSong.getTime();
        timeSignature = reSong.getTimeSignature();
        filename = reSong.getFilename();
        digitalOnly = reSong.getDigitalOnly();
        compilation = reSong.getCompilation();
        keyStart = reSong.getKeyStart();
        keyAccuracy = reSong.getKeyAccuracy();
        bpmStart = reSong.getBpmStart();
        bpmAccuracy = reSong.getBpmAccuracy();
        rating = reSong.getRating();
        dateAdded = reSong.getDateAdded();
        catalogId = reSong.getCatalogId();
        label = reSong.getLabel();
        remix = reSong.getRemix();
        numPlays = reSong.getNumPlays();
        comments = reSong.getComments();
        releaseDate = reSong.getReleaseDate();
        featuring = reSong.getFeaturing();
        keyEnd = reSong.getKeyEnd();
        disabled = reSong.getDisabled();
        bpmEnd = reSong.getBpmEnd();
        beatIntensity = reSong.getBeatIntensity();
        replayGain = reSong.getReplayGain();
        stylesBitmask = reSong.getStylesBitmask();
    }

    RESong::~RESong() {
    }

    void RESong::clear() {
        id = 0;
        songidWinfo.clear();
        songid.clear();
        shortid.clear();
        shortidWinfo.clear();
        artist.clear();
        album.clear();
        track.clear();
        title.clear();
        time.clear();
        timeSignature.clear();
        filename.clear();
        digitalOnly.clear();
        compilation.clear();
        keyStart.clear();
        keyAccuracy = 0;
        bpmStart.clear();
        bpmAccuracy = 0;
        rating = 0;
        dateAdded.clear();
        catalogId.clear();
        label.clear();
        remix.clear();
        numPlays = 0;
        comments.clear();
        releaseDate.clear();
        featuring.clear();
        keyEnd.clear();
        disabled.clear();
        bpmEnd.clear();
        beatIntensity = 0;
        replayGain.clear();
        stylesBitmask.clear();
    }

# pragma mark static methods

    void RESong::populateFields(const sql::ResultSet* rs, RESong* reSong) {
        reSong->setId(rs->getInt("id"));
        reSong->setSongidWinfo(rs->getString("songidWinfo"));
        reSong->setSongid(rs->getString("songid"));
        reSong->setShortid(rs->getString("shortid"));
        reSong->setShortidWinfo(rs->getString("shortidWinfo"));
        reSong->setArtist(rs->getString("artist"));
        reSong->setAlbum(rs->getString("album"));
        reSong->setTrack(rs->getString("track"));
        reSong->setTitle(rs->getString("title"));
        reSong->setTime(rs->getString("time"));
        reSong->setTimeSignature(rs->getString("timeSignature"));
        reSong->setFilename(rs->getString("filename"));
        reSong->setDigitalOnly(rs->getString("digitalOnly"));
        reSong->setCompilation(rs->getString("compilation"));
        reSong->setKeyStart(rs->getString("keyStart"));
        reSong->setKeyAccuracy(rs->getInt("keyAccuracy"));
        reSong->setBpmStart(rs->getString("bpmStart"));
        reSong->setBpmAccuracy(rs->getInt("bpmAccuracy"));
        reSong->setRating(rs->getInt("rating"));
        reSong->setDateAdded(rs->getString("dateAdded"));
        reSong->setCatalogId(rs->getString("catalogId"));
        reSong->setLabel(rs->getString("label"));
        reSong->setRemix(rs->getString("remix"));
        reSong->setNumPlays(rs->getInt("numPlays"));
        reSong->setComments(rs->getString("comments"));
        reSong->setReleaseDate(rs->getString("releaseDate"));
        reSong->setFeaturing(rs->getString("featuring"));
        reSong->setKeyEnd(rs->getString("keyEnd"));
        reSong->setDisabled(rs->getString("disabled"));
        reSong->setBpmEnd(rs->getString("bpmEnd"));
        reSong->setBeatIntensity(rs->getInt("beatIntensity"));
        reSong->setReplayGain(rs->getString("replayGain"));
    }

    RESong* RESong::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESongs where id = ?");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            RESong *reSong = NULL;
            if (rs->next()) {
                reSong = new RESong();
                populateFields(rs, reSong);
            }
            rs->close();
            delete rs;

            return reSong;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    RESong* RESong::findBySongid(const string& songid) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESongs where songid = ?");
            ps->setString(1, songid);
            sql::ResultSet *rs = ps->executeQuery();
            RESong *reSong = NULL;
            if (rs->next()) {
                reSong = new RESong();
                populateFields(rs, reSong);
            }
            rs->close();
            delete rs;

            return reSong;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<RESong>* RESong::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESongs");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<RESong> *dtrs = new ResultSetIterator<RESong>(rs);
        return dtrs;
    }

# pragma mark persistence

    bool RESong::sync() {
        RESong* reSong = findById(id);
        if (!reSong) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != reSong->getId()) {
            if (id) {
                cout << "updating reSong " << id << " id from " << reSong->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = reSong->getId();
            }
        }
        if (songidWinfo.compare(reSong->getSongidWinfo())  && (!boost::regex_match(songidWinfo, match1, decimal) || !boost::regex_match(reSong->getSongidWinfo(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!songidWinfo.empty()) {
                cout << "updating reSong " << id << " songidWinfo from " << reSong->getSongidWinfo() << " to " << songidWinfo << endl;
                needsUpdate = true;
            } else {
                songidWinfo = reSong->getSongidWinfo();
            }
        }
        if (songid.compare(reSong->getSongid())  && (!boost::regex_match(songid, match1, decimal) || !boost::regex_match(reSong->getSongid(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!songid.empty()) {
                cout << "updating reSong " << id << " songid from " << reSong->getSongid() << " to " << songid << endl;
                needsUpdate = true;
            } else {
                songid = reSong->getSongid();
            }
        }
        if (shortid.compare(reSong->getShortid())  && (!boost::regex_match(shortid, match1, decimal) || !boost::regex_match(reSong->getShortid(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!shortid.empty()) {
                cout << "updating reSong " << id << " shortid from " << reSong->getShortid() << " to " << shortid << endl;
                needsUpdate = true;
            } else {
                shortid = reSong->getShortid();
            }
        }
        if (shortidWinfo.compare(reSong->getShortidWinfo())  && (!boost::regex_match(shortidWinfo, match1, decimal) || !boost::regex_match(reSong->getShortidWinfo(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!shortidWinfo.empty()) {
                cout << "updating reSong " << id << " shortidWinfo from " << reSong->getShortidWinfo() << " to " << shortidWinfo << endl;
                needsUpdate = true;
            } else {
                shortidWinfo = reSong->getShortidWinfo();
            }
        }
        if (artist.compare(reSong->getArtist())  && (!boost::regex_match(artist, match1, decimal) || !boost::regex_match(reSong->getArtist(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!artist.empty()) {
                cout << "updating reSong " << id << " artist from " << reSong->getArtist() << " to " << artist << endl;
                needsUpdate = true;
            } else {
                artist = reSong->getArtist();
            }
        }
        if (album.compare(reSong->getAlbum())  && (!boost::regex_match(album, match1, decimal) || !boost::regex_match(reSong->getAlbum(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!album.empty()) {
                cout << "updating reSong " << id << " album from " << reSong->getAlbum() << " to " << album << endl;
                needsUpdate = true;
            } else {
                album = reSong->getAlbum();
            }
        }
        if (track.compare(reSong->getTrack())  && (!boost::regex_match(track, match1, decimal) || !boost::regex_match(reSong->getTrack(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!track.empty()) {
                cout << "updating reSong " << id << " track from " << reSong->getTrack() << " to " << track << endl;
                needsUpdate = true;
            } else {
                track = reSong->getTrack();
            }
        }
        if (title.compare(reSong->getTitle())  && (!boost::regex_match(title, match1, decimal) || !boost::regex_match(reSong->getTitle(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!title.empty()) {
                cout << "updating reSong " << id << " title from " << reSong->getTitle() << " to " << title << endl;
                needsUpdate = true;
            } else {
                title = reSong->getTitle();
            }
        }
        if (time.compare(reSong->getTime())  && (!boost::regex_match(time, match1, decimal) || !boost::regex_match(reSong->getTime(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!time.empty()) {
                cout << "updating reSong " << id << " time from " << reSong->getTime() << " to " << time << endl;
                needsUpdate = true;
            } else {
                time = reSong->getTime();
            }
        }
        if (timeSignature.compare(reSong->getTimeSignature())  && (!boost::regex_match(timeSignature, match1, decimal) || !boost::regex_match(reSong->getTimeSignature(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!timeSignature.empty()) {
                cout << "updating reSong " << id << " timeSignature from " << reSong->getTimeSignature() << " to " << timeSignature << endl;
                needsUpdate = true;
            } else {
                timeSignature = reSong->getTimeSignature();
            }
        }
        if (filename.compare(reSong->getFilename())  && (!boost::regex_match(filename, match1, decimal) || !boost::regex_match(reSong->getFilename(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!filename.empty()) {
                cout << "updating reSong " << id << " filename from " << reSong->getFilename() << " to " << filename << endl;
                needsUpdate = true;
            } else {
                filename = reSong->getFilename();
            }
        }
        if (digitalOnly.compare(reSong->getDigitalOnly())  && (!boost::regex_match(digitalOnly, match1, decimal) || !boost::regex_match(reSong->getDigitalOnly(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!digitalOnly.empty()) {
                cout << "updating reSong " << id << " digitalOnly from " << reSong->getDigitalOnly() << " to " << digitalOnly << endl;
                needsUpdate = true;
            } else {
                digitalOnly = reSong->getDigitalOnly();
            }
        }
        if (compilation.compare(reSong->getCompilation())  && (!boost::regex_match(compilation, match1, decimal) || !boost::regex_match(reSong->getCompilation(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!compilation.empty()) {
                cout << "updating reSong " << id << " compilation from " << reSong->getCompilation() << " to " << compilation << endl;
                needsUpdate = true;
            } else {
                compilation = reSong->getCompilation();
            }
        }
        if (keyStart.compare(reSong->getKeyStart())  && (!boost::regex_match(keyStart, match1, decimal) || !boost::regex_match(reSong->getKeyStart(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!keyStart.empty()) {
                cout << "updating reSong " << id << " keyStart from " << reSong->getKeyStart() << " to " << keyStart << endl;
                needsUpdate = true;
            } else {
                keyStart = reSong->getKeyStart();
            }
        }
        if (keyAccuracy != reSong->getKeyAccuracy()) {
            if (keyAccuracy) {
                cout << "updating reSong " << id << " keyAccuracy from " << reSong->getKeyAccuracy() << " to " << keyAccuracy << endl;
                needsUpdate = true;
            } else {
                keyAccuracy = reSong->getKeyAccuracy();
            }
        }
        if (bpmStart.compare(reSong->getBpmStart())  && (!boost::regex_match(bpmStart, match1, decimal) || !boost::regex_match(reSong->getBpmStart(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!bpmStart.empty()) {
                cout << "updating reSong " << id << " bpmStart from " << reSong->getBpmStart() << " to " << bpmStart << endl;
                needsUpdate = true;
            } else {
                bpmStart = reSong->getBpmStart();
            }
        }
        if (bpmAccuracy != reSong->getBpmAccuracy()) {
            if (bpmAccuracy) {
                cout << "updating reSong " << id << " bpmAccuracy from " << reSong->getBpmAccuracy() << " to " << bpmAccuracy << endl;
                needsUpdate = true;
            } else {
                bpmAccuracy = reSong->getBpmAccuracy();
            }
        }
        if (rating != reSong->getRating()) {
            if (rating) {
                cout << "updating reSong " << id << " rating from " << reSong->getRating() << " to " << rating << endl;
                needsUpdate = true;
            } else {
                rating = reSong->getRating();
            }
        }
        if (dateAdded.compare(reSong->getDateAdded())  && (!boost::regex_match(dateAdded, match1, decimal) || !boost::regex_match(reSong->getDateAdded(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!dateAdded.empty()) {
                cout << "updating reSong " << id << " dateAdded from " << reSong->getDateAdded() << " to " << dateAdded << endl;
                needsUpdate = true;
            } else {
                dateAdded = reSong->getDateAdded();
            }
        }
        if (catalogId.compare(reSong->getCatalogId())  && (!boost::regex_match(catalogId, match1, decimal) || !boost::regex_match(reSong->getCatalogId(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!catalogId.empty()) {
                cout << "updating reSong " << id << " catalogId from " << reSong->getCatalogId() << " to " << catalogId << endl;
                needsUpdate = true;
            } else {
                catalogId = reSong->getCatalogId();
            }
        }
        if (label.compare(reSong->getLabel())  && (!boost::regex_match(label, match1, decimal) || !boost::regex_match(reSong->getLabel(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!label.empty()) {
                cout << "updating reSong " << id << " label from " << reSong->getLabel() << " to " << label << endl;
                needsUpdate = true;
            } else {
                label = reSong->getLabel();
            }
        }
        if (remix.compare(reSong->getRemix())  && (!boost::regex_match(remix, match1, decimal) || !boost::regex_match(reSong->getRemix(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!remix.empty()) {
                cout << "updating reSong " << id << " remix from " << reSong->getRemix() << " to " << remix << endl;
                needsUpdate = true;
            } else {
                remix = reSong->getRemix();
            }
        }
        if (numPlays != reSong->getNumPlays()) {
            if (numPlays) {
                cout << "updating reSong " << id << " numPlays from " << reSong->getNumPlays() << " to " << numPlays << endl;
                needsUpdate = true;
            } else {
                numPlays = reSong->getNumPlays();
            }
        }
        if (comments.compare(reSong->getComments())  && (!boost::regex_match(comments, match1, decimal) || !boost::regex_match(reSong->getComments(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!comments.empty()) {
                cout << "updating reSong " << id << " comments from " << reSong->getComments() << " to " << comments << endl;
                needsUpdate = true;
            } else {
                comments = reSong->getComments();
            }
        }
        if (releaseDate.compare(reSong->getReleaseDate())  && (!boost::regex_match(releaseDate, match1, decimal) || !boost::regex_match(reSong->getReleaseDate(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!releaseDate.empty()) {
                cout << "updating reSong " << id << " releaseDate from " << reSong->getReleaseDate() << " to " << releaseDate << endl;
                needsUpdate = true;
            } else {
                releaseDate = reSong->getReleaseDate();
            }
        }
        if (featuring.compare(reSong->getFeaturing())  && (!boost::regex_match(featuring, match1, decimal) || !boost::regex_match(reSong->getFeaturing(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!featuring.empty()) {
                cout << "updating reSong " << id << " featuring from " << reSong->getFeaturing() << " to " << featuring << endl;
                needsUpdate = true;
            } else {
                featuring = reSong->getFeaturing();
            }
        }
        if (keyEnd.compare(reSong->getKeyEnd())  && (!boost::regex_match(keyEnd, match1, decimal) || !boost::regex_match(reSong->getKeyEnd(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!keyEnd.empty()) {
                cout << "updating reSong " << id << " keyEnd from " << reSong->getKeyEnd() << " to " << keyEnd << endl;
                needsUpdate = true;
            } else {
                keyEnd = reSong->getKeyEnd();
            }
        }
        if (disabled.compare(reSong->getDisabled())  && (!boost::regex_match(disabled, match1, decimal) || !boost::regex_match(reSong->getDisabled(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!disabled.empty()) {
                cout << "updating reSong " << id << " disabled from " << reSong->getDisabled() << " to " << disabled << endl;
                needsUpdate = true;
            } else {
                disabled = reSong->getDisabled();
            }
        }
        if (bpmEnd.compare(reSong->getBpmEnd())  && (!boost::regex_match(bpmEnd, match1, decimal) || !boost::regex_match(reSong->getBpmEnd(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!bpmEnd.empty()) {
                cout << "updating reSong " << id << " bpmEnd from " << reSong->getBpmEnd() << " to " << bpmEnd << endl;
                needsUpdate = true;
            } else {
                bpmEnd = reSong->getBpmEnd();
            }
        }
        if (beatIntensity != reSong->getBeatIntensity()) {
            if (beatIntensity) {
                cout << "updating reSong " << id << " beatIntensity from " << reSong->getBeatIntensity() << " to " << beatIntensity << endl;
                needsUpdate = true;
            } else {
                beatIntensity = reSong->getBeatIntensity();
            }
        }
        if (replayGain.compare(reSong->getReplayGain())  && (!boost::regex_match(replayGain, match1, decimal) || !boost::regex_match(reSong->getReplayGain(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!replayGain.empty()) {
                cout << "updating reSong " << id << " replayGain from " << reSong->getReplayGain() << " to " << replayGain << endl;
                needsUpdate = true;
            } else {
                replayGain = reSong->getReplayGain();
            }
        }
        return needsUpdate;
    }

    int RESong::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update RESongs set songidWinfo=?, songid=?, shortid=?, shortidWinfo=?, artist=?, album=?, track=?, title=?, time=?, timeSignature=?, filename=?, digitalOnly=?, compilation=?, keyStart=?, keyAccuracy=?, bpmStart=?, bpmAccuracy=?, rating=?, dateAdded=?, catalogId=?, label=?, remix=?, numPlays=?, comments=?, releaseDate=?, featuring=?, keyEnd=?, disabled=?, bpmEnd=?, beatIntensity=?, replayGain=? where id=?");
            ps->setString(1, songidWinfo);
            ps->setString(2, songid);
            ps->setString(3, shortid);
            ps->setString(4, shortidWinfo);
            ps->setString(5, artist);
            ps->setString(6, album);
            ps->setString(7, track);
            ps->setString(8, title);
            ps->setString(9, time);
            ps->setString(10, timeSignature);
            ps->setString(11, filename);
            ps->setString(12, digitalOnly);
            ps->setString(13, compilation);
            ps->setString(14, keyStart);
            ps->setInt(15, keyAccuracy);
            ps->setString(16, bpmStart);
            ps->setInt(17, bpmAccuracy);
            ps->setInt(18, rating);
            ps->setString(19, dateAdded);
            ps->setString(20, catalogId);
            ps->setString(21, label);
            ps->setString(22, remix);
            ps->setInt(23, numPlays);
            ps->setString(24, comments);
            ps->setString(25, releaseDate);
            ps->setString(26, featuring);
            ps->setString(27, keyEnd);
            ps->setString(28, disabled);
            ps->setString(29, bpmEnd);
            ps->setInt(30, beatIntensity);
            ps->setString(31, replayGain);
            ps->setInt(32, id);
            int result = ps->executeUpdate();
            return result;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    int RESong::save() {
        try {
            if (id == 0) {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select max(id) from RESongs");
                sql::ResultSet *rs = ps->executeQuery();
                rs->next();
                id = rs->getInt(1) + 1;
                rs->close();
                delete rs;
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into RESongs (id, songidWinfo, songid, shortid, shortidWinfo, artist, album, track, title, time, timeSignature, filename, digitalOnly, compilation, keyStart, keyAccuracy, bpmStart, bpmAccuracy, rating, dateAdded, catalogId, label, remix, numPlays, comments, releaseDate, featuring, keyEnd, disabled, bpmEnd, beatIntensity, replayGain) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            ps->setInt(1, id);
            ps->setString(2, songidWinfo);
            ps->setString(3, songid);
            ps->setString(4, shortid);
            ps->setString(5, shortidWinfo);
            ps->setString(6, artist);
            ps->setString(7, album);
            ps->setString(8, track);
            ps->setString(9, title);
            ps->setString(10, time);
            ps->setString(11, timeSignature);
            ps->setString(12, filename);
            ps->setString(13, digitalOnly);
            ps->setString(14, compilation);
            ps->setString(15, keyStart);
            ps->setInt(16, keyAccuracy);
            ps->setString(17, bpmStart);
            ps->setInt(18, bpmAccuracy);
            ps->setInt(19, rating);
            ps->setString(20, dateAdded);
            ps->setString(21, catalogId);
            ps->setString(22, label);
            ps->setString(23, remix);
            ps->setInt(24, numPlays);
            ps->setString(25, comments);
            ps->setString(26, releaseDate);
            ps->setString(27, featuring);
            ps->setString(28, keyEnd);
            ps->setString(29, disabled);
            ps->setString(30, bpmEnd);
            ps->setInt(31, beatIntensity);
            ps->setString(32, replayGain);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save reSong" << endl;
                return saved;
            } else {
                return saved;
            }
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }


# pragma mark accessors

    const int RESong::getId() const { return id; }
    void RESong::setId(const int id) { this->id = id; }

    const string& RESong::getSongidWinfo() const { return songidWinfo; }
    void RESong::setSongidWinfo(const string& songidWinfo) { this->songidWinfo = songidWinfo; }

    const string& RESong::getSongid() const { return songid; }
    void RESong::setSongid(const string& songid) { this->songid = songid; }

    const string& RESong::getShortid() const { return shortid; }
    void RESong::setShortid(const string& shortid) { this->shortid = shortid; }

    const string& RESong::getShortidWinfo() const { return shortidWinfo; }
    void RESong::setShortidWinfo(const string& shortidWinfo) { this->shortidWinfo = shortidWinfo; }

    const string& RESong::getArtist() const { return artist; }
    void RESong::setArtist(const string& artist) { this->artist = artist; }

    const string& RESong::getAlbum() const { return album; }
    void RESong::setAlbum(const string& album) { this->album = album; }

    const string& RESong::getTrack() const { return track; }
    void RESong::setTrack(const string& track) { this->track = track; }

    const string& RESong::getTitle() const { return title; }
    void RESong::setTitle(const string& title) { this->title = title; }

    const string& RESong::getTime() const { return time; }
    void RESong::setTime(const string& time) { this->time = time; }

    const string& RESong::getTimeSignature() const { return timeSignature; }
    void RESong::setTimeSignature(const string& timeSignature) { this->timeSignature = timeSignature; }

    const string& RESong::getFilename() const { return filename; }
    void RESong::setFilename(const string& filename) { this->filename = filename; }

    const string& RESong::getDigitalOnly() const { return digitalOnly; }
    void RESong::setDigitalOnly(const string& digitalOnly) { this->digitalOnly = digitalOnly; }

    const string& RESong::getCompilation() const { return compilation; }
    void RESong::setCompilation(const string& compilation) { this->compilation = compilation; }

    const string& RESong::getKeyStart() const { return keyStart; }
    void RESong::setKeyStart(const string& keyStart) { this->keyStart = keyStart; }

    const int RESong::getKeyAccuracy() const { return keyAccuracy; }
    void RESong::setKeyAccuracy(const int keyAccuracy) { this->keyAccuracy = keyAccuracy; }

    const string& RESong::getBpmStart() const { return bpmStart; }
    void RESong::setBpmStart(const string& bpmStart) { this->bpmStart = bpmStart; }

    const int RESong::getBpmAccuracy() const { return bpmAccuracy; }
    void RESong::setBpmAccuracy(const int bpmAccuracy) { this->bpmAccuracy = bpmAccuracy; }

    const int RESong::getRating() const { return rating; }
    void RESong::setRating(const int rating) { this->rating = rating; }

    const string& RESong::getDateAdded() const { return dateAdded; }
    void RESong::setDateAdded(const string& dateAdded) { this->dateAdded = dateAdded; }

    const string& RESong::getCatalogId() const { return catalogId; }
    void RESong::setCatalogId(const string& catalogId) { this->catalogId = catalogId; }

    const string& RESong::getLabel() const { return label; }
    void RESong::setLabel(const string& label) { this->label = label; }

    const string& RESong::getRemix() const { return remix; }
    void RESong::setRemix(const string& remix) { this->remix = remix; }

    const int RESong::getNumPlays() const { return numPlays; }
    void RESong::setNumPlays(const int numPlays) { this->numPlays = numPlays; }

    const string& RESong::getComments() const { return comments; }
    void RESong::setComments(const string& comments) { this->comments = comments; }

    const string& RESong::getReleaseDate() const { return releaseDate; }
    void RESong::setReleaseDate(const string& releaseDate) { this->releaseDate = releaseDate; }

    const string& RESong::getFeaturing() const { return featuring; }
    void RESong::setFeaturing(const string& featuring) { this->featuring = featuring; }

    const string& RESong::getKeyEnd() const { return keyEnd; }
    void RESong::setKeyEnd(const string& keyEnd) { this->keyEnd = keyEnd; }

    const string& RESong::getDisabled() const { return disabled; }
    void RESong::setDisabled(const string& disabled) { this->disabled = disabled; }

    const string& RESong::getBpmEnd() const { return bpmEnd; }
    void RESong::setBpmEnd(const string& bpmEnd) { this->bpmEnd = bpmEnd; }

    const int RESong::getBeatIntensity() const { return beatIntensity; }
    void RESong::setBeatIntensity(const int beatIntensity) { this->beatIntensity = beatIntensity; }

    const string& RESong::getReplayGain() const { return replayGain; }
    void RESong::setReplayGain(const string& replayGain) { this->replayGain = replayGain; }

    const string& RESong::getStylesBitmask() const { return stylesBitmask; }
    void RESong::setStylesBitmask(const string& stylesBitmask) { this->stylesBitmask = stylesBitmask; }

}
}
