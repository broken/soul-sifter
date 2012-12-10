//
//  Album.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/9/12.
//
//

#include "Album.h"

#include <string>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

using namespace std;

# pragma mark helpers

namespace {
    
    static void populateFields(const sql::ResultSet* rs, Album* album) {
        album->setId(rs->getInt("id"));
        album->setName(rs->getString("name"));
        album->setCoverFilepath(rs->getString("coverFilepath"));
        album->setMixed(rs->getBoolean("mixed"));
    }
}

#pragma mark initialization

Album::Album() :
id(0),
name(),
coverFilepath(),
mixed(false) {
}

Album::~Album() {
}

void Album::clear() {
    id = 0;
    name.clear();
    coverFilepath.clear();
    mixed = false;
}

#pragma mark static methods

Album* Album::findById(const int id) {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *rs = ps->executeQuery();
    Album *album = NULL;
    if (rs->next()) {
        album = new Album();
        populateFields(rs, album);
    }
    rs->close();
    delete rs;
    
    return album;
}

Album* Album::findByName(const string& name) {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where name = ?");
    ps->setString(1, name);
    sql::ResultSet *rs = ps->executeQuery();
    Album *album = NULL;
    if (rs->next()) {
        album = new Album();
        populateFields(rs, album);
    }
    rs->close();
    delete rs;
    
    return album;
}

Album* Album::findByCoverFilepath(const string& filepath) {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where coverFilepath = ?");
    ps->setString(1, filepath);
    sql::ResultSet *rs = ps->executeQuery();
    Album *album = NULL;
    if (rs->next()) {
        album = new Album();
        populateFields(rs, album);
    }
    rs->close();
    delete rs;
    
    return album;
}

#pragma mark persistence

bool Album::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Albums set name=?, coverFilepath=?, mixed=? where id=?");
        ps->setString(1, name);
        ps->setString(2, coverFilepath);
        ps->setBoolean(3, mixed);
        ps->setInt(4, id);
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

int Album::save() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Albums (name, coverFilepath, mixed) values (?,?,?)");
        ps->setString(1, name);
        ps->setString(2, coverFilepath);
        ps->setBoolean(3, mixed);
        ps->setInt(4, id);
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

#pragma mark accessors

const int Album::getId() const { return id; }
void Album::setId(const int id) { this->id = id; }

const string& Album::getName() const { return name; }
void Album::setName(const string& name) { this->name = name; }

const string& Album::getCoverFilepath() const { return coverFilepath; }
void Album::setCoverFilepath(const string& coverFilepath) { this->coverFilepath = coverFilepath; }

const bool Album::getMixed() const { return mixed; }
void Album::setMixed(const bool mixed) { this->mixed = mixed; }
