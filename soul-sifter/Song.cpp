//
//  Song.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/27/12.
//
//

#include "Song.h"

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "Album.h"
#include "MysqlAccess.h"
#include "RESong.h"

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
    reSongId(0),
    reSong(NULL),
    styles(),
    rating(0),
    albumId(0),
    album(NULL),
    dateAdded(0),
    comments(),
    trashed(false) {
    }
    
    Song::~Song() {
    }
    
    Song::Song(const Song& song) :
    id(song.getId()),
    artist(song.getArtist()),
    track(song.getTrack()),
    title(song.getTitle()),
    remix(song.getRemix()),
    featuring(song.getFeaturing()),
    filepath(song.getFilepath()),
    reSongId(song.getRESongId()),
    reSong(NULL),
    styles(),  // TODO copy styles
    rating(song.getRating()),
    albumId(song.getAlbumId()),
    album(NULL),
    dateAdded(song.getDateAdded()),
    comments(song.getComments()),
    trashed(song.getTrashed()) {
    }
    
    void Song::operator=(const Song& song) {
        id = song.getId();
        artist = song.getArtist();
        track = song.getTrack();
        title = song.getTitle();
        remix = song.getRemix();
        featuring = song.getFeaturing();
        filepath = song.getFilepath();
        reSongId = song.getRESongId();
        reSong = NULL;
        //styles;  // TODO copy styles
        rating = song.getRating();
        albumId = song.getAlbumId();
        album = NULL;
        dateAdded = song.getDateAdded();
        comments = song.getComments();
        trashed = song.getTrashed();
    }
    
    void Song::clear() {
        id = 0;
        artist.clear();
        track.clear();
        title.clear();
        remix.clear();
        featuring.clear();
        filepath.clear();
        reSongId = 0;
        delete reSong;
        reSong = NULL;
        styles.clear();
        rating = 0;
        albumId = 0;
        delete album;
        album = NULL;
        dateAdded = 0;
        comments.clear();
        trashed = false;
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
        song->setRESongId(rs->getInt("reSongId"));
        // TODO set styles
        song->setRating(rs->getInt("rating"));
        song->setAlbumId(rs->getInt("albumId"));
        song->setDateAdded(timeFromeString(rs->getString("dateAdded")));
        song->setComments(rs->getString("comments"));
        song->setTrashed(rs->getBoolean("trashed"));
    }
    
    Song* Song::findById(const int id) {
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
    
    Song* Song::findByRESongId(const int id) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Songs where reSongId = ?");
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
    
# pragma mark persistence
    
    bool Song::update() {
        try {
            if (album && album->sync()) {
                album->update();
            }
            if (reSong && reSong->sync()) {
                reSong->update();
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Song set artist=?, track=?, title=?, remix=?, featuring=?, filepath=?, reSongId=?, rating=?, albumId=?, dateAdded=?, comments=?, trashed=? where id=?");
            ps->setString(1, artist);
            ps->setString(2, track);
            ps->setString(3, title);
            ps->setString(4, remix);
            ps->setString(5, featuring);
            ps->setString(6, filepath);
            ps->setInt(7, reSongId);
            ps->setInt(8, rating);
            ps->setInt(9, albumId);
            ps->setString(10, getDateAddedString());
            ps->setString(11, comments);
            ps->setBoolean(12, trashed);
            ps->setInt(13, id);
            ps->executeUpdate();
            return true;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
            return false;
        }
    }
    
    const bool Song::save() {
        try {
            if (!albumId && album) {
                album->save();
                albumId = MysqlAccess::getInstance().getLastInsertId();
                album->setId(albumId);
            }
            if (reSong && reSong->needsSave()) {
                reSong->save();
                reSongId = reSong->getUniqueId();
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Songs (artist, track, title, remix, featuring, filepath, reSongId, rating, albumId, dateAdded, comments, trashed) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            ps->setString(1, artist);
            ps->setString(2, track);
            ps->setString(3, title);
            ps->setString(4, remix);
            ps->setString(5, featuring);
            ps->setString(6, filepath);
            ps->setInt(7, reSongId);
            ps->setInt(8, rating);
            ps->setInt(9, albumId);
            ps->setString(10, getDateAddedString());
            ps->setString(11, comments);
            ps->setBoolean(12, trashed);
            if (ps->executeUpdate() == 0) {
                return NULL;
            } else {
                const int id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cout << "ERROR: Inserted song, but unable to retrieve inserted ID." << endl;
                    return NULL;
                }
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into SongStyles (songId, styleId) values (?, ?)");
                for (vector<const Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, (*it)->getId());
                    ps->executeUpdate();
                }
                return findById(id);
            }
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
            return false;
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
    
    const int Song::getRESongId() const { return reSongId; }
    void Song::setRESongId(const int reSongId) { this->reSongId = reSongId; }
    
    const RESong* Song::getRESong() const {
        return reSong ? reSong : RESong::findByUniqueId(reSongId);
    }
    void Song::setRESong(RESong* reSong) {
        this->reSongId = reSong->getUniqueId();
        this->reSong = reSong;
    }
    
    const vector<const Style*> Song::getStyles() const { return styles; }
    void Song::setStyles(vector<const Style*> styles) { this->styles = styles; }
    void Song::addToStyle(const Style* style) { styles.push_back(style); }
    void Song::removeFromStyle(const Style* style) {
        for (vector<const Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
            if (style == (*it)) {
                styles.erase(it);
            }
        }
    }
    
    const int Song::getRating() const { return rating; }
    void Song::setRating(const int rating) { this->rating = rating; }
    
    const int Song::getAlbumId() const { return albumId; }
    void Song::setAlbumId(const int albumId) { this->albumId = albumId; }
    
    Album* Song::getAlbum() const {
        if (album) return album;
        if (albumId) {
            return Album::findById(albumId);
        }
        return album;
    }
    void Song::setAlbum(Album* album) {
        this->albumId = album->getId();
        this->album = album;
    }
    
    const time_t Song::getDateAdded() const { return dateAdded; }
    void Song::setDateAdded(const time_t dateAdded) { this->dateAdded = dateAdded; }
    
    const string& Song::getComments() const { return comments; }
    void Song::setComments(const string& comments) { this->comments = comments; }
    
    const bool Song::getTrashed() const { return trashed; }
    void Song::setTrashed(const bool trashed) { this->trashed = trashed; }
    
}
