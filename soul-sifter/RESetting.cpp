//
//  RESetting.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RESetting.h"

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

namespace {
    
    static void populateFields(const sql::ResultSet* rs, RESetting* setting) {
        setting->setId(rs->getInt("id"));
        setting->setName(rs->getString("name"));
        setting->setValue(rs->getString("value"));
    }
}

# pragma mark initialization

RESetting::RESetting() :
id(0),
name(),
value() {
}

RESetting::~RESetting() {
}

void RESetting::clear() {
    id = 0;
    name.clear();
    value.clear();
}

# pragma mark static methods

RESetting* RESetting::findById(const int id) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *rs = ps->executeQuery();
    RESetting *setting = NULL;
    if (rs->next()) {
        setting = new RESetting();
        populateFields(rs, setting);
    }
    rs->close();
    delete rs;
    
    return setting;
}

RESetting* RESetting::findByName(const string& name) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings where name = ?");
    ps->setString(1, name);
    sql::ResultSet *rs = ps->executeQuery();
    RESetting *setting = NULL;
    if (rs->next()) {
        setting = new RESetting();
        populateFields(rs, setting);
    }
    rs->close();
    delete rs;
    
    return setting;
}

void RESetting::findAll(vector<const RESetting*>* settings) {
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings");
    sql::ResultSet *rs = ps->executeQuery();
    while (rs->next()) {
        RESetting *setting = new RESetting();
        populateFields(rs, setting);
        settings->push_back(setting);
    }
    rs->close();
    delete rs;
}

# pragma mark persistence

bool RESetting::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update RESettings set name=?, value=? where id=?");
        ps->setString(1, name);
        ps->setString(2, value);
        ps->setInt(3, id);
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

RESetting* RESetting::save() {
    try {
        if (name.length() == 0) {
            return NULL;
        }
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into RESettings (name, value) values (?, ?)");
        ps->setString(1, name);
        ps->setString(2, value);
        if (ps->executeUpdate() == 0) {
            return NULL;
        } else {
            return findByName(name);
        }
	} catch (sql::SQLException &e) {
        cerr << "ERROR: SQLException in " << __FILE__;
        cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        cerr << "ERROR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return NULL;
	}
}

# pragma mark accessors

const int RESetting::getId() const { return id; }
void RESetting::setId(const int id) { this->id = id; }

const string& RESetting::getName() const { return name; }
void RESetting::setName(const string& name) { this->name = name; }

const string& RESetting::getValue() const { return value; }
string& RESetting::getValueRef() { return value; }
void RESetting::setValue(const string& value) { this->value = value; }

}
