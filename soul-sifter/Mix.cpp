//
//  Mix.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/3/12.
//
//

#include "Mix.h"

#include <iostream>
#include <string>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

using namespace std;

namespace soulsifter {

# pragma mark helpers

namespace {
    
    static void populateFields(const sql::ResultSet* rs, Mix* song) {
        song->setId(rs->getInt("id"));
        song->setOutSongId(rs->getInt("outSongId"));
        song->setInSongId(rs->getInt("inSongId"));
        song->setRank(rs->getInt("rank"));
        song->setBPMDiff(rs->getDouble("bpmDiff"));
        song->setComments(rs->getString("comments"));
        song->setAddon(rs->getBoolean("addon"));
    }
}

# pragma mark initialization

Mix::Mix() :
id(0),
outSongId(0),
outSong(),
inSongId(0),
inSong(),
rank(0),
bpmDiff(0),
comments(),
addon(false) {
}

Mix::~Mix() {
    delete outSong;
    outSong = NULL;
    delete inSong;
    inSong = NULL;
}

void Mix::clear() {
    id = 0;
    outSongId = 0;
    delete outSong;
    outSong = NULL;
    delete inSong;
    inSong = NULL;
    rank = 0;
    bpmDiff = 0;
    comments.clear();
    addon = false;
}

# pragma mark static

const Mix* Mix::findById(const int id) {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Mixes where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *rs = ps->executeQuery();
    Mix *mix = NULL;
    if (rs->next()) {
        mix = new Mix();
        populateFields(rs, mix);
    }
    rs->close();
    delete rs;
    return mix;
}

Mix* Mix::findBySongIds(const int outSongId, const int inSongId) {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Mixes where outSongId = ? and inSongId = ?");
    ps->setInt(1, outSongId);
    ps->setInt(2, inSongId);
    sql::ResultSet *rs = ps->executeQuery();
    Mix *mix = NULL;
    if (rs->next()) {
        mix = new Mix();
        populateFields(rs, mix);
    }
    rs->close();
    delete rs;
    return mix;
}

Mix::MixResultSet* Mix::findAll() {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Mixes");
    sql::ResultSet *rs = ps->executeQuery();
    MixResultSet *mrs = new MixResultSet(rs);
    return mrs;
}

# pragma mark persistence

bool Mix::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Mixes set outSongId=?, inSongId=?, bpmDiff=?, rank=?, comments=?, addon=? where id=?");
        ps->setInt(1, outSongId);
        ps->setInt(2, inSongId);
        ps->setDouble(3, bpmDiff);
        ps->setInt(4, rank);
        ps->setString(5, comments);
        ps->setBoolean(6, addon);
        ps->setInt(7, id);
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

int Mix::save() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Mixes (outSongId, inSongId, bpmDiff, rank, comments, addon) values (?, ?, ?, ?, ?, ?)");
        ps->setInt(1, outSongId);
        ps->setInt(2, inSongId);
        ps->setDouble(3, bpmDiff);
        ps->setInt(4, rank);
        ps->setString(5, comments);
        ps->setBoolean(6, addon);
        return ps->executeUpdate();
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return NULL;
	}
}

# pragma mark accessors

const int Mix::getId() const { return id; }
void Mix::setId(const int id) { this->id = id; }

const int Mix::getOutSongId() const { return outSongId; }
void Mix::setOutSongId(const int outSongId) {
    this->outSongId = outSongId;
    outSong = NULL;
}

const Song* Mix::getOutSong() {
    if (!outSong && outSongId)
        outSong = Song::findById(outSongId);
    return outSong;
}
void Mix::setOutSong(Song* song) {
    this->outSong = song;
    this->outSongId = song->getId();
}

const int Mix::getInSongId() const { return inSongId; }
void Mix::setInSongId(const int inSongId) {
    this->inSongId = inSongId;
    inSong = NULL;
}

const Song* Mix::getInSong() {
    if (!inSong && inSongId)
        inSong = Song::findById(inSongId);
    return inSong;
}
void Mix::setInSong(Song* song) {
    this->inSong = song;
    this->inSongId = song->getId();
}

const double Mix::getBPMDiff() const { return bpmDiff; }
void Mix::setBPMDiff(const double bpmDiff) { this->bpmDiff = bpmDiff; }

const int Mix::getRank() const { return rank; }
void Mix::setRank(const int rank) { this->rank = rank; }

const string& Mix::getComments() const { return comments; }
void Mix::setComments(const string& comments) { this->comments = comments; }

const bool Mix::getAddon() const { return addon; }
void Mix::setAddon(const bool addon) { this->addon = addon; }

# pragma mark MixResultSet

Mix::MixResultSet::MixResultSet(sql::ResultSet* resultset) :
rs(resultset) {
}

Mix::MixResultSet::~MixResultSet() {
    delete rs;
}

bool Mix::MixResultSet::next(Mix* mix) {
    if (rs->next()) {
        populateFields(rs, mix);
        return true;
    } else {
        return false;
    }
}

}