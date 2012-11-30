//
//  Song.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/27/12.
//
//

#include "Song.h"

#include <vector>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "BasicGenre.h"
#include "MysqlAccess.h"
#include "RESong.h"

# pragma mark helpers

namespace {
    
    static void populateFields(const sql::ResultSet* rs, Song* song) {
        song->setId(rs->getInt("id"));
        song->setArtist(rs->getString("artist"));
        song->setTrack(rs->getString("track"));
        song->setTitle(rs->getString("title"));
        song->setRemix(rs->getString("remix"));
        song->setFeaturing(rs->getString("featuring"));
        song->setLabel(rs->getString("label"));
        song->setCatalogId(rs->getString("catalogId"));
        song->setReleaseDateYear(rs->getInt("releaseDateYear"));
        song->setReleaseDateMonth(rs->getInt("releaseDateMonth"));
        song->setReleaseDateDay(rs->getInt("releaseDateDay"));
        song->setFilepath(rs->getString("filepath"));
        song->setBasicGenreId(rs->getInt("basicGenreId"));
        song->setBasicGenre(BasicGenre::findById(song->getBasicGenreId()));
        song->setRESongId(rs->getInt("reSongId"));
        song->setRESong(RESong::findByUniqueId(song->getRESongId()));
        // TODO set styles
    }
}

# pragma mark initialization

Song::Song() :
id(0),
artist(),
album(),
track(),
title(),
remix(),
featuring(),
label(),
catalogId(),
releaseDateYear(),
releaseDateMonth(),
releaseDateDay(),
filepath(),
basicGenreId(0),
basicGenre(),
reSongId(0),
reSong(),
styles() {
}

Song::~Song() {
}

# pragma mark static methods

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
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Song set artist=?, album=?, track=?, title=?, remix=?, featuring=?, label=?, catalogId=?, releaseDateYear=?, releaseDateMonth=?, releaseDateDay=?, filepath=?, basicGenreId=?, reSongId=? where id=?");
        ps->setString(1, artist);
        ps->setString(2, album);
        ps->setString(3, track);
        ps->setString(4, title);
        ps->setString(5, remix);
        ps->setString(6, featuring);
        ps->setString(7, label);
        ps->setString(8, catalogId);
        ps->setInt(9, releaseDateYear);
        ps->setInt(10, releaseDateMonth);
        ps->setInt(11, releaseDateDay);
        ps->setString(12, filepath);
        ps->setInt(13, basicGenreId);
        ps->setInt(14, reSongId);
        ps->setInt(15, id);
        ps->executeUpdate();
        return true;
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
	}
}

const Song* Song::save() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Songs set (artist, album, track, title, remix, featuring, label, catalogId, releaseDateYear, releaseDateMonth, releaseDateDay, filepath, basicGenreId, reSongId) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        ps->setString(1, artist);
        ps->setString(2, album);
        ps->setString(3, track);
        ps->setString(4, title);
        ps->setString(5, remix);
        ps->setString(6, featuring);
        ps->setString(7, label);
        ps->setString(8, catalogId);
        ps->setInt(9, releaseDateYear);
        ps->setInt(10, releaseDateMonth);
        ps->setInt(11, releaseDateDay);
        ps->setString(12, filepath);
        ps->setInt(13, basicGenreId);
        ps->setInt(14, reSongId);
        if (ps->executeUpdate() == 0) {
            return NULL;
        } else {
            const int id = MysqlAccess::getInstance().getLastInsertId();
            if (id == 0) {
                cout << "ERROR: Inserted song, but unable to retrieve inserted ID." << endl;
            } else {
                return findById(id);
            }
        }
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
	}
}

# pragma mark accessors

const int Song::getId() const { return id; }
void Song::setId(const int id) { this->id = id; }

const string& Song::getArtist() const { return artist; }
void Song::setArtist(const string& artist) { this->artist = artist; }

const string& Song::getAlbum() const { return album; }
void Song::setAlbum(const string& album) { this->album = album; }

const string& Song::getTrack() const { return track; }
void Song::setTrack(const string& track) { this->track = track; }

const string& Song::getTitle() const { return title; }
void Song::setTitle(const string& title) { this->title = title; }

const string& Song::getRemix() const { return remix; }
void Song::setRemix(const string& remix) { this->remix = remix; }

const string& Song::getFeaturing() const { return featuring; }
void Song::setFeaturing(const string& featuring) { this->featuring = featuring; }

const string& Song::getLabel() const { return label; }
void Song::setLabel(const string& label) { this->label = label; }

const string& Song::getCatalogId() const { return catalogId; }
void Song::setCatalogId(const string& catalogId) { this->catalogId = catalogId; }

const int Song::getReleaseDateYear() const { return releaseDateYear; }
void Song::setReleaseDateYear(const int releaseDateYear) { this->releaseDateYear = releaseDateYear; }

const int Song::getReleaseDateMonth() const { return releaseDateMonth; }
void Song::setReleaseDateMonth(const int releaseDateMonth) { this->releaseDateMonth = releaseDateMonth; }

const int Song::setReleaseDateDay() const { return releaseDateDay; }
void Song::setReleaseDateDay(const int releaseDateDay) { this->releaseDateDay = releaseDateDay; }

const string& Song::getFilepath() const { return filepath; }
void Song::setFilepath(const string& filepath) { this->filepath = filepath; }

const int Song::getBasicGenreId() const { return basicGenreId; }
void Song::setBasicGenreId(const int basicGenreId) { this->basicGenreId = basicGenreId; }

const BasicGenre* Song::getBasicGenre() const {
    return basicGenre ? basicGenre : BasicGenre::findById(basicGenreId);
}
void Song::setBasicGenre(const BasicGenre* basicGenre) { this->basicGenre = basicGenre; }

const int Song::getRESongId() const { return reSongId; }
void Song::setRESongId(const int reSongId) { this->reSongId = reSongId; }

const RESong* Song::getRESong() const {
    return reSong ? reSong : RESong::findByUniqueId(reSongId);
}
void Song::setRESong(RESong* reSong) { this->reSong = reSong; }

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
