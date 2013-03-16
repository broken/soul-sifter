//
//  RESong.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "RESong.h"

#include <string>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"
#include "DTVectorUtil.h"

using namespace std;

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

    dogatech::ResultSetIterator<RESong>* RESong::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESongs");
        sql::ResultSet *rs = ps->executeQuery();
        dogatech::ResultSetIterator<RESong> *dtrs = new dogatech::ResultSetIterator<RESong>(rs);
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
        if (id != reSong->getId()) {
            if (id) {
                cout << "updating reSong " << id << " id from " << reSong->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = reSong->getId();
            }
        }
        if (songidWinfo.compare(reSong->getSongidWinfo()) && (!atoi(reSong->getSongidWinfo().c_str()) || !atoi(songidWinfo.c_str()) || atoi(reSong->getSongidWinfo().c_str()) != atoi(songidWinfo.c_str()))) {
            if (!songidWinfo.empty()) {
                cout << "updating reSong " << id << " songidWinfo from " << reSong->getSongidWinfo() << " to " << songidWinfo << endl;
                needsUpdate = true;
            } else {
                songidWinfo = reSong->getSongidWinfo();
            }
        }
        if (songid.compare(reSong->getSongid()) && (!atoi(reSong->getSongid().c_str()) || !atoi(songid.c_str()) || atoi(reSong->getSongid().c_str()) != atoi(songid.c_str()))) {
            if (!songid.empty()) {
                cout << "updating reSong " << id << " songid from " << reSong->getSongid() << " to " << songid << endl;
                needsUpdate = true;
            } else {
                songid = reSong->getSongid();
            }
        }
        if (shortid.compare(reSong->getShortid()) && (!atoi(reSong->getShortid().c_str()) || !atoi(shortid.c_str()) || atoi(reSong->getShortid().c_str()) != atoi(shortid.c_str()))) {
            if (!shortid.empty()) {
                cout << "updating reSong " << id << " shortid from " << reSong->getShortid() << " to " << shortid << endl;
                needsUpdate = true;
            } else {
                shortid = reSong->getShortid();
            }
        }
        if (shortidWinfo.compare(reSong->getShortidWinfo()) && (!atoi(reSong->getShortidWinfo().c_str()) || !atoi(shortidWinfo.c_str()) || atoi(reSong->getShortidWinfo().c_str()) != atoi(shortidWinfo.c_str()))) {
            if (!shortidWinfo.empty()) {
                cout << "updating reSong " << id << " shortidWinfo from " << reSong->getShortidWinfo() << " to " << shortidWinfo << endl;
                needsUpdate = true;
            } else {
                shortidWinfo = reSong->getShortidWinfo();
            }
        }
        if (artist.compare(reSong->getArtist()) && (!atoi(reSong->getArtist().c_str()) || !atoi(artist.c_str()) || atoi(reSong->getArtist().c_str()) != atoi(artist.c_str()))) {
            if (!artist.empty()) {
                cout << "updating reSong " << id << " artist from " << reSong->getArtist() << " to " << artist << endl;
                needsUpdate = true;
            } else {
                artist = reSong->getArtist();
            }
        }
        if (album.compare(reSong->getAlbum()) && (!atoi(reSong->getAlbum().c_str()) || !atoi(album.c_str()) || atoi(reSong->getAlbum().c_str()) != atoi(album.c_str()))) {
            if (!album.empty()) {
                cout << "updating reSong " << id << " album from " << reSong->getAlbum() << " to " << album << endl;
                needsUpdate = true;
            } else {
                album = reSong->getAlbum();
            }
        }
        if (track.compare(reSong->getTrack()) && (!atoi(reSong->getTrack().c_str()) || !atoi(track.c_str()) || atoi(reSong->getTrack().c_str()) != atoi(track.c_str()))) {
            if (!track.empty()) {
                cout << "updating reSong " << id << " track from " << reSong->getTrack() << " to " << track << endl;
                needsUpdate = true;
            } else {
                track = reSong->getTrack();
            }
        }
        if (title.compare(reSong->getTitle()) && (!atoi(reSong->getTitle().c_str()) || !atoi(title.c_str()) || atoi(reSong->getTitle().c_str()) != atoi(title.c_str()))) {
            if (!title.empty()) {
                cout << "updating reSong " << id << " title from " << reSong->getTitle() << " to " << title << endl;
                needsUpdate = true;
            } else {
                title = reSong->getTitle();
            }
        }
        if (time.compare(reSong->getTime()) && (!atoi(reSong->getTime().c_str()) || !atoi(time.c_str()) || atoi(reSong->getTime().c_str()) != atoi(time.c_str()))) {
            if (!time.empty()) {
                cout << "updating reSong " << id << " time from " << reSong->getTime() << " to " << time << endl;
                needsUpdate = true;
            } else {
                time = reSong->getTime();
            }
        }
        if (timeSignature.compare(reSong->getTimeSignature()) && (!atoi(reSong->getTimeSignature().c_str()) || !atoi(timeSignature.c_str()) || atoi(reSong->getTimeSignature().c_str()) != atoi(timeSignature.c_str()))) {
            if (!timeSignature.empty()) {
                cout << "updating reSong " << id << " timeSignature from " << reSong->getTimeSignature() << " to " << timeSignature << endl;
                needsUpdate = true;
            } else {
                timeSignature = reSong->getTimeSignature();
            }
        }
        if (filename.compare(reSong->getFilename()) && (!atoi(reSong->getFilename().c_str()) || !atoi(filename.c_str()) || atoi(reSong->getFilename().c_str()) != atoi(filename.c_str()))) {
            if (!filename.empty()) {
                cout << "updating reSong " << id << " filename from " << reSong->getFilename() << " to " << filename << endl;
                needsUpdate = true;
            } else {
                filename = reSong->getFilename();
            }
        }
        if (digitalOnly.compare(reSong->getDigitalOnly()) && (!atoi(reSong->getDigitalOnly().c_str()) || !atoi(digitalOnly.c_str()) || atoi(reSong->getDigitalOnly().c_str()) != atoi(digitalOnly.c_str()))) {
            if (!digitalOnly.empty()) {
                cout << "updating reSong " << id << " digitalOnly from " << reSong->getDigitalOnly() << " to " << digitalOnly << endl;
                needsUpdate = true;
            } else {
                digitalOnly = reSong->getDigitalOnly();
            }
        }
        if (compilation.compare(reSong->getCompilation()) && (!atoi(reSong->getCompilation().c_str()) || !atoi(compilation.c_str()) || atoi(reSong->getCompilation().c_str()) != atoi(compilation.c_str()))) {
            if (!compilation.empty()) {
                cout << "updating reSong " << id << " compilation from " << reSong->getCompilation() << " to " << compilation << endl;
                needsUpdate = true;
            } else {
                compilation = reSong->getCompilation();
            }
        }
        if (keyStart.compare(reSong->getKeyStart()) && (!atoi(reSong->getKeyStart().c_str()) || !atoi(keyStart.c_str()) || atoi(reSong->getKeyStart().c_str()) != atoi(keyStart.c_str()))) {
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
        if (bpmStart.compare(reSong->getBpmStart()) && (!atoi(reSong->getBpmStart().c_str()) || !atoi(bpmStart.c_str()) || atoi(reSong->getBpmStart().c_str()) != atoi(bpmStart.c_str()))) {
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
        if (dateAdded.compare(reSong->getDateAdded()) && (!atoi(reSong->getDateAdded().c_str()) || !atoi(dateAdded.c_str()) || atoi(reSong->getDateAdded().c_str()) != atoi(dateAdded.c_str()))) {
            if (!dateAdded.empty()) {
                cout << "updating reSong " << id << " dateAdded from " << reSong->getDateAdded() << " to " << dateAdded << endl;
                needsUpdate = true;
            } else {
                dateAdded = reSong->getDateAdded();
            }
        }
        if (catalogId.compare(reSong->getCatalogId()) && (!atoi(reSong->getCatalogId().c_str()) || !atoi(catalogId.c_str()) || atoi(reSong->getCatalogId().c_str()) != atoi(catalogId.c_str()))) {
            if (!catalogId.empty()) {
                cout << "updating reSong " << id << " catalogId from " << reSong->getCatalogId() << " to " << catalogId << endl;
                needsUpdate = true;
            } else {
                catalogId = reSong->getCatalogId();
            }
        }
        if (label.compare(reSong->getLabel()) && (!atoi(reSong->getLabel().c_str()) || !atoi(label.c_str()) || atoi(reSong->getLabel().c_str()) != atoi(label.c_str()))) {
            if (!label.empty()) {
                cout << "updating reSong " << id << " label from " << reSong->getLabel() << " to " << label << endl;
                needsUpdate = true;
            } else {
                label = reSong->getLabel();
            }
        }
        if (remix.compare(reSong->getRemix()) && (!atoi(reSong->getRemix().c_str()) || !atoi(remix.c_str()) || atoi(reSong->getRemix().c_str()) != atoi(remix.c_str()))) {
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
        if (comments.compare(reSong->getComments()) && (!atoi(reSong->getComments().c_str()) || !atoi(comments.c_str()) || atoi(reSong->getComments().c_str()) != atoi(comments.c_str()))) {
            if (!comments.empty()) {
                cout << "updating reSong " << id << " comments from " << reSong->getComments() << " to " << comments << endl;
                needsUpdate = true;
            } else {
                comments = reSong->getComments();
            }
        }
        if (releaseDate.compare(reSong->getReleaseDate()) && (!atoi(reSong->getReleaseDate().c_str()) || !atoi(releaseDate.c_str()) || atoi(reSong->getReleaseDate().c_str()) != atoi(releaseDate.c_str()))) {
            if (!releaseDate.empty()) {
                cout << "updating reSong " << id << " releaseDate from " << reSong->getReleaseDate() << " to " << releaseDate << endl;
                needsUpdate = true;
            } else {
                releaseDate = reSong->getReleaseDate();
            }
        }
        if (featuring.compare(reSong->getFeaturing()) && (!atoi(reSong->getFeaturing().c_str()) || !atoi(featuring.c_str()) || atoi(reSong->getFeaturing().c_str()) != atoi(featuring.c_str()))) {
            if (!featuring.empty()) {
                cout << "updating reSong " << id << " featuring from " << reSong->getFeaturing() << " to " << featuring << endl;
                needsUpdate = true;
            } else {
                featuring = reSong->getFeaturing();
            }
        }
        if (keyEnd.compare(reSong->getKeyEnd()) && (!atoi(reSong->getKeyEnd().c_str()) || !atoi(keyEnd.c_str()) || atoi(reSong->getKeyEnd().c_str()) != atoi(keyEnd.c_str()))) {
            if (!keyEnd.empty()) {
                cout << "updating reSong " << id << " keyEnd from " << reSong->getKeyEnd() << " to " << keyEnd << endl;
                needsUpdate = true;
            } else {
                keyEnd = reSong->getKeyEnd();
            }
        }
        if (disabled.compare(reSong->getDisabled()) && (!atoi(reSong->getDisabled().c_str()) || !atoi(disabled.c_str()) || atoi(reSong->getDisabled().c_str()) != atoi(disabled.c_str()))) {
            if (!disabled.empty()) {
                cout << "updating reSong " << id << " disabled from " << reSong->getDisabled() << " to " << disabled << endl;
                needsUpdate = true;
            } else {
                disabled = reSong->getDisabled();
            }
        }
        if (bpmEnd.compare(reSong->getBpmEnd()) && (!atoi(reSong->getBpmEnd().c_str()) || !atoi(bpmEnd.c_str()) || atoi(reSong->getBpmEnd().c_str()) != atoi(bpmEnd.c_str()))) {
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
        if (replayGain.compare(reSong->getReplayGain()) && (!atoi(reSong->getReplayGain().c_str()) || !atoi(replayGain.c_str()) || atoi(reSong->getReplayGain().c_str()) != atoi(replayGain.c_str()))) {
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
