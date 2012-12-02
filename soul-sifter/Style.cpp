//
//  Style.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/9/12.
//
//

#include "Style.h"

#include <iostream>
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

# pragma mark helpers

namespace {
    
    static void populateFields(const sql::ResultSet* rs, Style* style) {
        style->setId(rs->getInt("id"));
        style->setName(rs->getString("name"));
        style->setREId(rs->getInt("re_id"));
        style->setREName(rs->getString("re_name"));
    }
}

# pragma mark initialization

Style::Style() :
id(0),
name(),
re_id(0),
re_name() {
}

Style::~Style() {
}

void Style::clear() {
    id = 0;
    name.clear();
    re_id = 0;
    re_name.clear();
}

# pragma mark static methods

const Style* Style::findById(const int id) {
    static vector<const Style*> styles;
    
    // first check for our static genre
    for (vector<const Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
        if ((*it)->id == id) {
            return *it;
        }
    }
    
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles where id = ?");
    ps->setInt(1, id);
    sql::ResultSet *rs = ps->executeQuery();
    Style *style = NULL;
    if (rs->next()) {
        style = new Style();
        populateFields(rs, style);
    }
    rs->close();
    delete rs;
    
    // add to static
    styles.push_back(style);
    
    return style;
}

const Style* Style::findByREId(const int re_id) {
    static vector<const Style*> styles;
    
    // first check for our static genre
    for (vector<const Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
        if ((*it)->re_id == re_id) {
            return *it;
        }
    }
    
    // lookup in db
    sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles where re_id = ?");
    ps->setInt(1, re_id);
    sql::ResultSet *rs = ps->executeQuery();
    Style *style = NULL;
    if (rs->next()) {
        style = new Style();
        populateFields(rs, style);
    }
    rs->close();
    delete rs;
    
    // add to static
    styles.push_back(style);
    
    return style;
}

bool Style::findStyle(Style* style) {
    try {
        // use various means to try and retrieve the style
        sql::ResultSet *result;
        if (style->id > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select id, name, re_id, re_name from styles where id = ?");
            ps->setInt(1, style->id);
            result = ps->executeQuery();
        } else if (style->re_name.length() > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select id, name, re_id, re_name from styles where re_name = ?");
            ps->setString(1, style->re_name);
            result = ps->executeQuery();
        } else if (style->re_id > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select id, name, re_id, re_name from styles where re_id = ?");
            ps->setInt(1, style->re_id);
            result = ps->executeQuery();
        } else if (style->name.length() > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select id, name, re_id, re_name from styles where name = ?");
            ps->setString(1, style->name);
            result = ps->executeQuery();
        } else {
            cout << "Nothing to search for style by" << endl;
            return false;
        }
        
        // did we get a unique result?
        if (!result->next()) {
            cout << "No style found." << endl;
            return false;
        } else if (!result->isLast()) {
            cout << "Ambigious result returned." << endl;
            return false;
        }
        
        // update fields
        if (style->id != result->getInt("id")) {
            if (style->id > 0)
                cout << "updating id of style from " << style->id << " to " << result->getInt("id") << endl;
            style->id = result->getInt("id");
        }
        if (style->re_id != result->getInt("re_id")) {
            if (style->re_id > 0)
                cout << "updating re_id of style from " << style->re_id << " to " << result->getInt("re_id") << endl;
            style->re_id = result->getInt("re_id");
        }
        if (style->name.compare(result->getString("name"))) {
            if (style->name.length() > 0)
                cout << "updating name of style from " << style->name << " to " << result->getInt("name") << endl;
            style->name = result->getString("name");
        }
        if (style->re_name.compare(result->getString("re_name"))) {
            if (style->re_name.length() > 0)
                cout << "updating re_name of style from " << style->re_name << " to " << result->getInt("re_name") << endl;
            style->re_name = result->getString("re_name");
        }
        
        // clean up
        delete result;
        
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

# pragma mark persistence

bool Style::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update styles set name=?, re_id=?, re_name=? where id=?");
        ps->setString(1, name);
        ps->setInt(2, re_id);
        ps->setString(3, re_name);
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

const Style* Style::save() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into styles (name, re_id, re_name) values (?, ?, ?)");
        ps->setString(1, name);
        ps->setInt(2, re_id);
        ps->setString(3, re_name);
        if (ps->executeUpdate() == 0) {
            return NULL;
        } else {
            const int id = MysqlAccess::getInstance().getLastInsertId();
            if (id == 0) {
                cout << "ERROR: Inserted style, but unable to retrieve inserted ID." << endl;
            } else {
                return findById(id);
            }
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

const int Style::getId() const { return id; }
void Style::setId(const int id) { this->id = id; }

const string& Style::getName() const { return name; }
void Style::setName(const string& name) { this->name = name; }

const int Style::getREId() const { return re_id; }
void Style::setREId(const int re_id) { this->re_id = re_id; }

const string& Style::getREName() const { return re_name; }
void Style::setREName(const string& re_name) { this->re_name = re_name; }
