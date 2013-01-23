//
//  BasicGenre.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "BasicGenre.h"

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

# pragma mark initialization

    BasicGenre::BasicGenre() :
    id(0),
    name() {
    }

    BasicGenre::BasicGenre(const BasicGenre& basicGenre) :
    id(basicGenre.getId()),
    name(basicGenre.getName()) {
    }

    void BasicGenre::operator=(const BasicGenre& basicGenre) {
        id = basicGenre.getId();
        name = basicGenre.getName();
    }

    BasicGenre::~BasicGenre() {
    }

    void BasicGenre::clear() {
        id = 0;
        name.clear();
    }

# pragma mark static methods

    void BasicGenre::populateFields(const sql::ResultSet* rs, BasicGenre* basicGenre) {
        basicGenre->setId(rs->getInt("id"));
        basicGenre->setName(rs->getString("name"));
    }

    BasicGenre* BasicGenre::findById(int id) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres where id = ?");
        ps->setInt(1, id);
        sql::ResultSet *rs = ps->executeQuery();
        BasicGenre *basicGenre = NULL;
        if (rs->next()) {
            basicGenre = new BasicGenre();
            populateFields(rs, basicGenre);
        }
        rs->close();
        delete rs;

        return basicGenre;
    }

    BasicGenre* BasicGenre::findByName(const string& name) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres where name = ?");
        ps->setString(1, name);
        sql::ResultSet *rs = ps->executeQuery();
        BasicGenre *basicGenre = NULL;
        if (rs->next()) {
            basicGenre = new BasicGenre();
            populateFields(rs, basicGenre);
        }
        rs->close();
        delete rs;

        return basicGenre;
    }

# pragma mark persistence

    bool BasicGenre::sync() {
        BasicGenre* basicGenre = findById(id);
        if (!basicGenre) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        if (id != basicGenre->getId()) {
            if (id) {
                cout << "updating basicGenre's id from " << basicGenre->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = basicGenre->getId();
            }
        }
        if (name.compare(basicGenre->getName())) {
            if (!name.empty()) {
                cout << "updating basicGenre name from " << basicGenre->getName() << " to " << name << endl;
                needsUpdate = true;
            } else {
                name = basicGenre->getName();
            }
        }
        return needsUpdate;
    }

    int BasicGenre::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update BasicGenres set name=? where id=?");
            ps->setString(1, name);
            ps->setInt(2, id);
            return ps->executeUpdate();
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            return 0;
        }
    }

    int BasicGenre::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into BasicGenres (name) values (?)");
            ps->setString(1, name);
            return ps->executeUpdate();
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

    const int BasicGenre::getId() const { return id; }
    void BasicGenre::setId(const int id) { this->id = id; }

    const string& BasicGenre::getName() const { return name; }
    void BasicGenre::setName(const string& name) { this->name = name; }

}
