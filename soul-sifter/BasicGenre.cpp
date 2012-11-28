//
//  BasicGenre.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/27/12.
//
//

#include "BasicGenre.h"

#include <vector>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

using namespace std;

#pragma mark initialization

BasicGenre::BasicGenre() :
id(0),
name() {
}

BasicGenre::~BasicGenre() {
}

#pragma mark static methods

const BasicGenre* BasicGenre::findById(const int id) {
    static vector<BasicGenre*> basicGenres;
    
    // first check for our static genre
    for (vector<BasicGenre*>::iterator it = basicGenres.begin(); it != basicGenres.end(); ++it) {
        if ((*it)->id == id) {
            return *it;
        }
    }
    
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *result = ps->executeQuery();
    if (!result->next()) {
        return NULL;
    }
    BasicGenre *genre = new BasicGenre();
    genre->setId(result->getInt("id"));
    genre->setName(result->getString("name"));
    delete result;
    
    // add to static
    basicGenres.push_back(genre);
    
    return genre;
}

const BasicGenre* BasicGenre::findByName(const string& name) {
    static vector<BasicGenre*> basicGenres;
    
    // first check for our static genre
    for (vector<BasicGenre*>::iterator it = basicGenres.begin(); it != basicGenres.end(); ++it) {
        if (!(*it)->name.compare(name)) {
            return *it;
        }
    }
    
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres where name = ?");
    ps->setString(1, name);
    sql::ResultSet *result = ps->executeQuery();
    if (!result->next()) {
        return NULL;
    }
    BasicGenre *genre = new BasicGenre();
    genre->setId(result->getInt("id"));
    genre->setName(result->getString("name"));
    delete result;
    
    // add to static
    basicGenres.push_back(genre);
    
    return genre;
}

#pragma mark persistence

bool BasicGenre::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update BasicGenres set name=? where id=?");
        ps->setString(1, name);
        ps->setInt(2, id);
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

const BasicGenre* BasicGenre::save() {
    try {
        if (name.length() == 0) {
            return NULL;
        }
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into BasicGenres (name) values (?)");
        ps->setString(1, name);
        if (ps->executeUpdate() == 0) {
            return NULL;
        } else {
            return findByName(name);
        }
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return NULL;
	}
}

#pragma mark accessors

const int BasicGenre::getId() const { return id; }
void BasicGenre::setId(const int id) { this->id = id; }

const string& BasicGenre::getName() const { return name; }
void BasicGenre::setName(const string& name) { this->name = name; }
