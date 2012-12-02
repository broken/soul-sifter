//
//  REXML.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "REXML.h"

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

using namespace std;

namespace {
    
    static void populateFields(const sql::ResultSet* rs, REXML* xml) {
        xml->setId(rs->getInt("id"));
        xml->setName(rs->getString("name"));
        xml->setXml(rs->getString("xml"));
    }
}

#pragma mark initialization

REXML::REXML() :
id(0),
name(),
xml() {
}

REXML::~REXML() {
}

#pragma mark static methods

REXML* REXML::findById(const int id) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REXML where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *rs = ps->executeQuery();
    REXML *xml = NULL;
    if (rs->next()) {
        xml = new REXML();
        populateFields(rs, xml);
    }
    rs->close();
    delete rs;
    
    return xml;
}

REXML* REXML::findByName(const string& name) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REXML where name = ?");
    ps->setString(1, name);
    sql::ResultSet *rs = ps->executeQuery();
    REXML *xml = NULL;
    if (rs->next()) {
        xml = new REXML();
        populateFields(rs, xml);
    }
    rs->close();
    delete rs;
    
    return xml;
}

#pragma mark persistence

bool REXML::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update REXML set name=?, xml=? where id=?");
        ps->setString(1, name);
        ps->setString(2, xml);
        ps->setInt(3, id);
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

REXML* REXML::save() {
    try {
        if (name.length() == 0) {
            return NULL;
        }
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into REXML (name, xml) values (?, ?)");
        ps->setString(1, name);
        ps->setString(2, xml);
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

void REXML::clear() {
    id = 0;
    name.clear();
    xml.clear();
}

#pragma mark accessors

const int REXML::getId() const { return id; }
void REXML::setId(const int id) { this->id = id; }

const string& REXML::getName() const { return name; }
void REXML::setName(const string& name) { this->name = name; }

const string& REXML::getXml() const { return xml; }
string& REXML::getXmlRef() { return xml; }
void REXML::setXml(const string& xml) { this->xml = xml; }
