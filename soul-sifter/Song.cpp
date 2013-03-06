//
//  Song.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Song.h"

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

    Song::Song() :
    id(0),
    artist(),
    track(),
    title(),
    remix(),
    featuring(),
    filepath(),
    rating(0),
    dateAdded(NULL),
    comments(),
    trashed(false),
    reSongId(0),
    reSong(NULL),
    albumId(0),
    album(NULL),
    styles(),
    stylesIds() {
    }

    Song::Song(const Song& song) :
    id(song.getId()),
    artist(song.getArtist()),
    track(song.getTrack()),
    title(song.getTitle()),
    remix(song.getRemix()),
    featuring(song.getFeaturing()),
    filepath(song.getFilepath()),
    rating(song.getRating()),
    dateAdded(song.getDateAdded()),
    comments(song.getComments()),
    trashed(song.getTrashed()),
    reSongId(song.getRESongId()),
    reSong(NULL),
    albumId(song.getAlbumId()),
    album(NULL),
    styles(),
    stylesIds(song.stylesIds) {
    }

    void Song::operator=(const Song& song) {
        id = song.getId();
        artist = song.getArtist();
        track = song.getTrack();
        title = song.getTitle();
        remix = song.getRemix();
        featuring = song.getFeaturing();
        filepath = song.getFilepath();
        rating = song.getRating();
        dateAdded = song.getDateAdded();
        comments = song.getComments();
        trashed = song.getTrashed();
        reSongId = song.getRESongId();
        reSong = NULL;
        albumId = song.getAlbumId();
        album = NULL;
        stylesIds = song.stylesIds;
    }

    Song::~Song() {
        delete reSong;
        reSong = NULL;
        delete album;
        album = NULL;
        while (!styles.empty()) delete styles.back(), styles.pop_back();
    }

    void Song::clear() {
        id = 0;
        artist.clear();
        track.clear();
        title.clear();
        remix.clear();
        featuring.clear();
        filepath.clear();
        rating = 0;
        dateAdded = 0;
        comments.clear();
        trashed = false;
        reSongId = 0;
        delete reSong;
        reSong = NULL;
        albumId = 0;
        delete album;
        album = NULL;
        for (vector<Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
            delete *it;
        }
        styles.clear();
        stylesIds.clear();
    }

# pragma mark static methods

    void Song::populateFields(const sql::ResultSet* rs, Song* song) {
        song->setId(rs->getInt("id"));
        song->setArtist(rs->getString("artist"));
        song->setTrack(rs->getString("track"));
        song->setTitle(rs->getString("title"));
        song->setRemix(rs->getString("remix"));
        song->setFeaturing(rs->getString("featuring"));
        song->setFilepath(rs->getString("filepath"));
        song->setRating(rs->getInt("rating"));
        song->setDateAdded(timeFromString(rs->getString("dateAdded")));
        song->setComments(rs->getString("comments"));
        song->setTrashed(rs->getBoolean("trashed"));
        song->setRESongId(rs->getInt("reSongId"));
        song->setAlbumId(rs->getInt("albumId"));
        populateStylesIds(song);
    }

    void Song::populateStylesIds(Song* song) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select styleId from SongStyles where songId = ?");
        ps->setInt(1, song->getId());
        sql::ResultSet *rs = ps->executeQuery();
        while (rs->next()) {
            song->stylesIds.push_back(rs->getInt(1));
        }
        rs->close();
        delete rs;
    }

    Song* Song::findById(int id) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Songs where id = ?");
        ps->setInt(1, id);
        sql::ResultSet *rs = ps->executeQuery();
        Song *song = NULL;
        if (rs->next()) {
            song = new Song();
            populateFields(rs, song);
        }
        rs->close();
        delete rs;

        return song;
    }

    Song* Song::findByRESongId(int reSongId) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Songs where reSongId = ?");
        ps->setInt(1, reSongId);
        sql::ResultSet *rs = ps->executeQuery();
        Song *song = NULL;
        if (rs->next()) {
            song = new Song();
            populateFields(rs, song);
        }
        rs->close();
        delete rs;

        return song;
    }

# pragma mark persistence

    bool Song::sync() {
        Song* song = findById(id);
        if (!song) song = findByRESongId(reSongId);
        if (!song) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        if (id != song->getId()) {
            if (id) {
                cout << "updating song's id from " << song->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = song->getId();
            }
        }
        if (artist.compare(song->getArtist())) {
            if (!artist.empty()) {
                cout << "updating song artist from " << song->getArtist() << " to " << artist << endl;
                needsUpdate = true;
            } else {
                artist = song->getArtist();
            }
        }
        if (track.compare(song->getTrack())) {
            if (!track.empty()) {
                cout << "updating song track from " << song->getTrack() << " to " << track << endl;
                needsUpdate = true;
            } else {
                track = song->getTrack();
            }
        }
        if (title.compare(song->getTitle())) {
            if (!title.empty()) {
                cout << "updating song title from " << song->getTitle() << " to " << title << endl;
                needsUpdate = true;
            } else {
                title = song->getTitle();
            }
        }
        if (remix.compare(song->getRemix())) {
            if (!remix.empty()) {
                cout << "updating song remix from " << song->getRemix() << " to " << remix << endl;
                needsUpdate = true;
            } else {
                remix = song->getRemix();
            }
        }
        if (featuring.compare(song->getFeaturing())) {
            if (!featuring.empty()) {
                cout << "updating song featuring from " << song->getFeaturing() << " to " << featuring << endl;
                needsUpdate = true;
            } else {
                featuring = song->getFeaturing();
            }
        }
        if (filepath.compare(song->getFilepath())) {
            if (!filepath.empty()) {
                cout << "updating song filepath from " << song->getFilepath() << " to " << filepath << endl;
                needsUpdate = true;
            } else {
                filepath = song->getFilepath();
            }
        }
        if (rating != song->getRating()) {
            if (rating) {
                cout << "updating song's rating from " << song->getRating() << " to " << rating << endl;
                needsUpdate = true;
            } else {
                rating = song->getRating();
            }
        }
        if (dateAdded != song->getDateAdded()) {
            if (dateAdded) {
                cout << "updating song's dateAdded from " << song->getDateAdded() << " to " << dateAdded << endl;
                needsUpdate = true;
            } else {
                dateAdded = song->getDateAdded();
            }
        }
        if (comments.compare(song->getComments())) {
            if (!comments.empty()) {
                cout << "updating song comments from " << song->getComments() << " to " << comments << endl;
                needsUpdate = true;
            } else {
                comments = song->getComments();
            }
        }
        if (trashed != song->getTrashed()) {
            if (trashed) {
                cout << "updating song's trashed from " << song->getTrashed() << " to " << trashed << endl;
                needsUpdate = true;
            } else {
                trashed = song->getTrashed();
            }
        }
        if (reSongId != song->getRESongId()) {
            if (reSongId) {
                cout << "updating song's reSongId from " << song->getRESongId() << " to " << reSongId << endl;
                needsUpdate = true;
            } else {
                reSongId = song->getRESongId();
            }
        }
        if (albumId != song->getAlbumId()) {
            if (albumId) {
                cout << "updating song's albumId from " << song->getAlbumId() << " to " << albumId << endl;
                needsUpdate = true;
            } else {
                albumId = song->getAlbumId();
            }
        }
        if (!dogatech::equivalentVectors<int>(stylesIds, song->stylesIds)) {
            if (!dogatech::containsVector<int>(stylesIds, song->stylesIds)) {
                cout << "updating song stylesIds" << endl;
                needsUpdate = true;
            }
            dogatech::appendUniqueVector<int>(song->stylesIds, &stylesIds);
            styles.clear();
        }
        return needsUpdate;
    }

    int Song::update() {
        try {
            if (reSong && reSong->sync()) {
                reSong->update();
            }
            if (album && album->sync()) {
                album->update();
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Songs set artist=?, track=?, title=?, remix=?, featuring=?, filepath=?, rating=?, dateAdded=?, comments=?, trashed=?, reSongId=?, albumId=? where id=?");
            ps->setString(1, artist);
            ps->setString(2, track);
            ps->setString(3, title);
            ps->setString(4, remix);
            ps->setString(5, featuring);
            ps->setString(6, filepath);
            ps->setInt(7, rating);
            ps->setString(8, stringFromTime(dateAdded));
            ps->setString(9, comments);
            ps->setBoolean(10, trashed);
            ps->setInt(11, reSongId);
            ps->setInt(12, albumId);
            ps->setInt(13, id);
            int result = ps->executeUpdate();
            if (!stylesIds.empty()) {
                ps = MysqlAccess::getInstance().getPreparedStatement("insert ignore into SongStyles (songId, styleId) values (?, ?)");
                for (vector<int>::const_iterator it = stylesIds.begin(); it != stylesIds.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, *it);
                    ps->executeUpdate();
                }
            }
            return result;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            return 0;
        }
    }

    int Song::save() {
        try {
            if (reSong && (!reSong->getId() || !RESong::findById(reSong->getId()))) {
                if (reSong->save()) {
                    if (reSong->getId()) {
                        reSongId = reSong->getId();
                    } else {
                        reSongId = MysqlAccess::getInstance().getLastInsertId();
                        reSong->setId(reSongId);
                    }
                } else {
                    cerr << "Unable to save reSong" << endl;
                }
            }
            if (album && (!album->getId() || !Album::findById(album->getId()))) {
                if (album->save()) {
                    if (album->getId()) {
                        albumId = album->getId();
                    } else {
                        albumId = MysqlAccess::getInstance().getLastInsertId();
                        album->setId(albumId);
                    }
                } else {
                    cerr << "Unable to save album" << endl;
                }
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Songs (artist, track, title, remix, featuring, filepath, rating, dateAdded, comments, trashed, reSongId, albumId) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            ps->setString(1, artist);
            ps->setString(2, track);
            ps->setString(3, title);
            ps->setString(4, remix);
            ps->setString(5, featuring);
            ps->setString(6, filepath);
            ps->setInt(7, rating);
            ps->setString(8, stringFromTime(dateAdded));
            ps->setString(9, comments);
            ps->setBoolean(10, trashed);
            ps->setInt(11, reSongId);
            ps->setInt(12, albumId);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save song" << endl;
                return 0;
            } else {
                const int id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted song, but unable to retreive inserted ID." << endl;
                    return 0;
                }
                sql::PreparedStatement *ps;
                ps = MysqlAccess::getInstance().getPreparedStatement("insert into SongStyles (songId, styleId) values (?, ?)");
                for (vector<Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, (*it)->getId());
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save style for song" << endl;
                    }
                }
                return 1;
            }
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            return 0;
        }
    }


# pragma mark accessors

    const int Song::getId() const { return id; }
    void Song::setId(const int id) { this->id = id; }

    const string& Song::getArtist() const { return artist; }
    void Song::setArtist(const string& artist) { this->artist = artist; }

    const string& Song::getTrack() const { return track; }
    void Song::setTrack(const string& track) { this->track = track; }

    const string& Song::getTitle() const { return title; }
    void Song::setTitle(const string& title) { this->title = title; }

    const string& Song::getRemix() const { return remix; }
    void Song::setRemix(const string& remix) { this->remix = remix; }

    const string& Song::getFeaturing() const { return featuring; }
    void Song::setFeaturing(const string& featuring) { this->featuring = featuring; }

    const string& Song::getFilepath() const { return filepath; }
    void Song::setFilepath(const string& filepath) { this->filepath = filepath; }

    const int Song::getRating() const { return rating; }
    void Song::setRating(const int rating) { this->rating = rating; }

    const time_t Song::getDateAdded() const { return dateAdded; }
    void Song::setDateAdded(const time_t dateAdded) { this->dateAdded = dateAdded; }

    const string& Song::getComments() const { return comments; }
    void Song::setComments(const string& comments) { this->comments = comments; }

    const bool Song::getTrashed() const { return trashed; }
    void Song::setTrashed(const bool trashed) { this->trashed = trashed; }

    const int Song::getRESongId() const { return reSongId; }
    void Song::setRESongId(const int reSongId) {
        this->reSongId = reSongId;
        delete reSong;
        reSong = NULL;
    }

    RESong* Song::getRESong() const {
        if (!reSong && reSongId)
            return RESong::findById(reSongId);
        return reSong;
    }
    void Song::setRESong(const RESong& reSong) {
        this->reSongId = reSong.getId();
        delete this->reSong;
        this->reSong = new RESong(reSong);
    }

    const int Song::getAlbumId() const { return albumId; }
    void Song::setAlbumId(const int albumId) {
        this->albumId = albumId;
        delete album;
        album = NULL;
    }

    Album* Song::getAlbum() const {
        if (!album && albumId)
            return Album::findById(albumId);
        return album;
    }
    void Song::setAlbum(const Album& album) {
        this->albumId = album.getId();
        delete this->album;
        this->album = new Album(album);
    }

    const vector<Style*>& Song::getStyles() {
        if (styles.empty() && !stylesIds.empty()) {
            for (vector<int>::const_iterator it = stylesIds.begin(); it != stylesIds.end(); ++it) {
                styles.push_back(Style::findById(*it));
            }
        }
        return styles;
    }
    void Song::setStyles(const vector<Style*>& styles) { this->styles = styles; }
    void Song::addStyle(const Style& style) { styles.push_back(new Style(style)); }
    void Song::removeStyle(int styleId) {
        for (vector<Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
            if (styleId == (*it)->getId()) {
                styles.erase(it);
            }
        }
    }

}
