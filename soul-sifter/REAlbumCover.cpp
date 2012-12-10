//
//  REAlbumCover.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "REAlbumCover.h"

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

using namespace std;

namespace soulsifter {

namespace {
    
    static void populateFields(const sql::ResultSet* rs, REAlbumCover* ac) {
        ac->setId(rs->getInt("id"));
        ac->setREId(rs->getString("re_id"));
        ac->setThumbnail(rs->getString("thumbnail"));
    }
}

#pragma mark initialization

REAlbumCover::REAlbumCover() :
id(0),
reId(),
thumbnail() {
}

REAlbumCover::~REAlbumCover() {
}

#pragma mark static methods

REAlbumCover* REAlbumCover::findById(const int id) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REAlbumCovers where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *rs = ps->executeQuery();
    REAlbumCover *ac = NULL;
    if (rs->next()) {
        ac = new REAlbumCover();
        populateFields(rs, ac);
    }
    rs->close();
    delete rs;
    
    return ac;
}

REAlbumCover* REAlbumCover::findByREId(const string& reId) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REAlbumCovers where re_id = ?");
    ps->setString(1, reId);
    sql::ResultSet *rs = ps->executeQuery();
    REAlbumCover *ac = NULL;
    if (rs->next()) {
        ac = new REAlbumCover();
        populateFields(rs, ac);
    }
    rs->close();
    delete rs;
    
    return ac;
}

REAlbumCover::REAlbumCoverIterator* REAlbumCover::findAll() {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REAlbumCovers");
    sql::ResultSet *rs = ps->executeQuery();
    REAlbumCoverIterator *it = new REAlbumCoverIterator(rs);
    return it;
}

#pragma mark persistence

int REAlbumCover::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update REAlbumCovers set re_id=?, thumbnail=? where id=?");
        ps->setString(1, reId);
        ps->setString(2, thumbnail);
        ps->setInt(3, id);
        return ps->executeUpdate();
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return 0;
	}
}

int REAlbumCover::save() {
    try {
        if (reId.length() == 0) {
            return NULL;
        }
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into REAlbumCovers (re_id, thumbnail) values (?, ?)");
        ps->setString(1, reId);
        ps->setString(2, thumbnail);
        return ps->executeUpdate();
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return 0;
	}
}

void REAlbumCover::clear() {
    id = 0;
    reId.clear();
    thumbnail.clear();
}

#pragma mark accessors

const int REAlbumCover::getId() const { return id; }
void REAlbumCover::setId(const int id) { this->id = id; }

const string& REAlbumCover::getREId() const { return reId; }
void REAlbumCover::setREId(const string& reId) { this->reId = reId; }

const string& REAlbumCover::getThumbnail() const { return thumbnail; }
void REAlbumCover::setThumbnail(const string& thumbnail) { this->thumbnail = thumbnail; }

# pragma mark RESongIterator

REAlbumCover::REAlbumCoverIterator::REAlbumCoverIterator(sql::ResultSet* resultset) :
rs(resultset) {
}

REAlbumCover::REAlbumCoverIterator::~REAlbumCoverIterator() {
    delete rs;
}

bool REAlbumCover::REAlbumCoverIterator::next(REAlbumCover* albumcover) {
    if (rs->next()) {
        populateFields(rs, albumcover);
        return true;
    } else {
        return false;
    }
}

}
