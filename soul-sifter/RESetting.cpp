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

namespace {
    
    static void populateFields(const sql::ResultSet* rs, RESetting* setting) {
        setting->setName(rs->getString("name"));
        setting->setValue(rs->getString("value"));
    }
}

#pragma mark initialization

RESetting::RESetting() :
name(),
value() {
}

RESetting::~RESetting() {
}

#pragma mark static methods

RESetting* RESetting::findByName(const string& name) {
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings where name = ?");
    ps->setString(1, name);
    sql::ResultSet *rs = ps->executeQuery();
    RESetting *setting = NULL;
    if (rs->next()) {
        populateFields(rs, setting);
    }
    rs->close();
    delete rs;
    
    return setting;
}

#pragma mark persistence

bool RESetting::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update RESettings set value=? where name=?");
        ps->setString(1, value);
        ps->setString(2, name);
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
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return NULL;
	}
}

#pragma mark accessors

const string& RESetting::getName() const { return name; }
void RESetting::setName(const string& name) { this->name = name; }

const string& RESetting::getValue() const { return value; }
void RESetting::setValue(const string& value) { this->value = value; }
