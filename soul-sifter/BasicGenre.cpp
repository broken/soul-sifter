//
//  BasicGenre.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/27/12.
//
//

#include "BasicGenre.h"

#include <string>
#include <vector>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

using namespace std;

namespace soulsifter {
    
#pragma mark initialization
    
    BasicGenre::BasicGenre() :
    id(0),
    name() {
    }
    
    BasicGenre::~BasicGenre() {
    }
    
#pragma mark static methods
    
    void BasicGenre::populateFields(const sql::ResultSet* rs, BasicGenre* genre) {
        genre->setId(rs->getInt("id"));
        genre->setName(rs->getString("name"));
    }
    
    const BasicGenre* BasicGenre::findById(const int id) {
        static vector<const BasicGenre*> basicGenres;
        
        // first check for our static genre
        for (vector<const BasicGenre*>::iterator it = basicGenres.begin(); it != basicGenres.end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        
        // lookup in db
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres where id = ?");
        ps->setInt(1, id);
        sql::ResultSet *rs = ps->executeQuery();
        BasicGenre *genre = NULL;
        if (rs->next()) {
            genre = new BasicGenre();
            populateFields(rs, genre);
        }
        rs->close();
        delete rs;
        
        // add to static
        if (genre)
            basicGenres.push_back(genre);
        
        return genre;
    }
    
    const BasicGenre* BasicGenre::findByName(const string& name) {
        static vector<const BasicGenre*> basicGenres;
        
        // first check for our static genre
        for (vector<const BasicGenre*>::iterator it = basicGenres.begin(); it != basicGenres.end(); ++it) {
            if (!(*it)->name.compare(name)) {
                return *it;
            }
        }
        
        // lookup in db
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres where name = ?");
        ps->setString(1, name);
        sql::ResultSet *rs = ps->executeQuery();
        BasicGenre *genre = NULL;
        if (rs->next()) {
            genre = new BasicGenre();
            populateFields(rs, genre);
        }
        rs->close();
        delete rs;
        
        // add to static
        if (genre)
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
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
            return false;
        }
    }
    
    int BasicGenre::save() {
        try {
            if (name.length() == 0) {
                return NULL;
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into BasicGenres (name) values (?)");
            ps->setString(1, name);
            return ps->executeUpdate();
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
            return NULL;
        }
    }
    
#pragma mark accessors
    
    const int BasicGenre::getId() const { return id; }
    void BasicGenre::setId(const int id) { this->id = id; }
    
    const string& BasicGenre::getName() const { return name; }
    void BasicGenre::setName(const string& name) { this->name = name; }
    
}