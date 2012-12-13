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

namespace soulsifter {

# pragma mark helpers

namespace {
    
    struct lessThanKey {
        inline bool operator()(const Style* v1, const Style* v2) {
            return (*v1) < (*v2);
        }
    };
    
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
re_name(),
children(),
parents() {
}

Style::~Style() {
}

void Style::clear() {
    id = 0;
    name.clear();
    re_id = 0;
    re_name.clear();
    children.clear();
    parents.clear();
}

# pragma mark operator overrides

bool Style::operator<(const Style& style) const {
    return name.compare(style.getName()) < 0;
}

bool Style::operator>(const Style& style) const {
    return name.compare(style.getName()) > 0;
}

# pragma mark static methods

Style* Style::findByIdMutable(const int id) {
    vector<Style*>* styles = getStaticStyles();
    for (vector<Style*>::iterator it = styles->begin(); it != styles->end(); ++it) {
        if ((*it)->id == id) {
            return *it;
        }
    }
    return NULL;
}

const Style* Style::findById(const int id) {
    return findByIdMutable(id);
}

Style* Style::findByREId(const int re_id) {
    vector<Style*>* styles = getStaticStyles();
    for (vector<Style*>::iterator it = styles->begin(); it != styles->end(); ++it) {
        if ((*it)->re_id == re_id) {
            return *it;
        }
    }
    return NULL;
}

void Style::findAll(const vector<Style*>** stylesPtr) {
    vector<Style*>* styles = getStaticStyles();
    (*stylesPtr) = styles;
}

void Style::findAllSorted(const vector<Style*>** stylesPtr) {
    vector<Style*>* styles = getStaticStyles();
    sort(styles->begin(), styles->end(), lessThanKey());
    (*stylesPtr) = styles;
}

vector<Style*>* Style::getStaticStyles() {
    static vector<Style*> styles;
    if (styles.empty()) {
        // get all styles
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles");
        sql::ResultSet *rs = ps->executeQuery();
        while (rs->next()) {
            for (vector<Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
                if ((*it)->id == rs->getInt("id")) {
                    continue;
                }
            }
            Style *style = new Style();
            populateFields(rs, style);
            styles.push_back(style);
        }
        rs->close();
        delete rs;
    
        // set all parents & children
        ps = MysqlAccess::getInstance().getPreparedStatement("select * from StyleChildren");
        rs = ps->executeQuery();
        while (rs->next()) {
            Style *parent = findByIdMutable(rs->getInt("parentId"));
            Style *child = findByIdMutable(rs->getInt("childId"));
            child->parents.push_back(parent);
            parent->children.push_back(child);
        }
        rs->close();
        delete rs;
    }
    return &styles;
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
        cerr << "ERROR: SQLException in " << __FILE__;
        cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        cerr << "ERROR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
	}
}

int Style::save() {
    try {
        vector<Style*>* styles = getStaticStyles();
        
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Styles (name, re_id, re_name) values (?, ?, ?)");
        ps->setString(1, name);
        ps->setInt(2, re_id);
        ps->setString(3, re_name);
        int result = ps->executeUpdate();
        
        // add to static styles
        ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles where re_id = ?");
        ps->setInt(1, re_id);
        sql::ResultSet *rs = ps->executeQuery();
        Style *style = NULL;
        if (rs->next()) {
            style = new Style();
            populateFields(rs, style);
            styles->push_back(style);
        } else {
            cout << "Error: cannot find newly saved style" << endl;
        }
        rs->close();
        delete rs;
        
        return result;
	} catch (sql::SQLException &e) {
        cerr << "ERROR: SQLException in " << __FILE__;
        cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        cerr << "ERROR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return NULL;
	}
}

int Style::addChild(Style* child) {
    try {
        for (vector<Style*>::const_iterator it = children.begin(); it != children.end(); ++it) {
            if ((*it)->getId() == child->getId()) {
                return 0;
            }
        }
        children.push_back(child);
        child->parents.push_back(this);
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into StyleChildren (parentId, childId) values (?, ?)");
        ps->setInt(1, id);
        ps->setInt(2, child->getId());
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

const int Style::getId() const { return id; }
void Style::setId(const int id) { this->id = id; }

const string& Style::getName() const { return name; }
void Style::setName(const string& name) { this->name = name; }

const int Style::getREId() const { return re_id; }
void Style::setREId(const int re_id) { this->re_id = re_id; }

const string& Style::getREName() const { return re_name; }
void Style::setREName(const string& re_name) { this->re_name = re_name; }

void Style::getChildren(const vector<Style*>** stylesPtr) const {
    getStaticStyles();
    (*stylesPtr) = &children;
}

void Style::getParents(const vector<Style*>** stylesPtr) const {
    getStaticStyles();
    (*stylesPtr) = &parents;
}

}
