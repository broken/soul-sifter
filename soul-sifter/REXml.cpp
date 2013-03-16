//
//  REXml.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "REXml.h"

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

    REXml::REXml() :
    id(0),
    name(),
    xml() {
    }

    REXml::REXml(const REXml& reXml) :
    id(reXml.getId()),
    name(reXml.getName()),
    xml(reXml.getXml()) {
    }

    void REXml::operator=(const REXml& reXml) {
        id = reXml.getId();
        name = reXml.getName();
        xml = reXml.getXml();
    }

    REXml::~REXml() {
    }

    void REXml::clear() {
        id = 0;
        name.clear();
        xml.clear();
    }

# pragma mark static methods

    void REXml::populateFields(const sql::ResultSet* rs, REXml* reXml) {
        reXml->setId(rs->getInt("id"));
        reXml->setName(rs->getString("name"));
        reXml->setXml(rs->getString("xml"));
    }

    REXml* REXml::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REXml where id = ?");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            REXml *reXml = NULL;
            if (rs->next()) {
                reXml = new REXml();
                populateFields(rs, reXml);
            }
            rs->close();
            delete rs;

            return reXml;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    REXml* REXml::findByName(const string& name) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REXml where name = ?");
            ps->setString(1, name);
            sql::ResultSet *rs = ps->executeQuery();
            REXml *reXml = NULL;
            if (rs->next()) {
                reXml = new REXml();
                populateFields(rs, reXml);
            }
            rs->close();
            delete rs;

            return reXml;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    dogatech::ResultSetIterator<REXml>* REXml::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REXml");
        sql::ResultSet *rs = ps->executeQuery();
        dogatech::ResultSetIterator<REXml> *dtrs = new dogatech::ResultSetIterator<REXml>(rs);
        return dtrs;
    }

# pragma mark persistence

    bool REXml::sync() {
        REXml* reXml = findById(id);
        if (!reXml) reXml = findByName(name);
        if (!reXml) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        if (id != reXml->getId()) {
            if (id) {
                cout << "updating reXml " << id << " id from " << reXml->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = reXml->getId();
            }
        }
        if (name.compare(reXml->getName()) && (!atoi(reXml->getName().c_str()) || !atoi(name.c_str()) || atoi(reXml->getName().c_str()) != atoi(name.c_str()))) {
            if (!name.empty()) {
                cout << "updating reXml " << id << " name from " << reXml->getName() << " to " << name << endl;
                needsUpdate = true;
            } else {
                name = reXml->getName();
            }
        }
        if (xml.compare(reXml->getXml()) && (!atoi(reXml->getXml().c_str()) || !atoi(xml.c_str()) || atoi(reXml->getXml().c_str()) != atoi(xml.c_str()))) {
            if (!xml.empty()) {
                cout << "updating reXml " << id << " xml from " << reXml->getXml() << " to " << xml << endl;
                needsUpdate = true;
            } else {
                xml = reXml->getXml();
            }
        }
        return needsUpdate;
    }

    int REXml::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update REXml set name=?, xml=? where id=?");
            ps->setString(1, name);
            ps->setString(2, xml);
            ps->setInt(3, id);
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

    int REXml::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into REXml (name, xml) values (?, ?)");
            ps->setString(1, name);
            ps->setString(2, xml);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save reXml" << endl;
                return saved;
            } else {
                const int id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted reXml, but unable to retreive inserted ID." << endl;
                    return saved;
                }
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

    const int REXml::getId() const { return id; }
    void REXml::setId(const int id) { this->id = id; }

    const string& REXml::getName() const { return name; }
    void REXml::setName(const string& name) { this->name = name; }

    const string& REXml::getXml() const { return xml; }
    void REXml::setXml(const string& xml) { this->xml = xml; }

}
