//
//  Style.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Style.h"

#include <cmath>
#include <string>

#include <boost/regex.hpp>

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

    Style::Style() :
    id(0),
    name(),
    reId(0),
    reLabel(),
    children(),
    childrenIds(),
    parents(),
    parentsIds() {
    }

    Style::Style(const Style& style) :
    id(style.getId()),
    name(style.getName()),
    reId(style.getREId()),
    reLabel(style.getRELabel()),
    children(),
    childrenIds(style.childrenIds),
    parents(),
    parentsIds(style.parentsIds) {
    }

    void Style::operator=(const Style& style) {
        id = style.getId();
        name = style.getName();
        reId = style.getREId();
        reLabel = style.getRELabel();
        childrenIds = style.childrenIds;
        parentsIds = style.parentsIds;
    }

    Style::~Style() {
        while (!children.empty()) delete children.back(), children.pop_back();
        while (!parents.empty()) delete parents.back(), parents.pop_back();
    }

    void Style::clear() {
        id = 0;
        name.clear();
        reId = 0;
        reLabel.clear();
        for (vector<Style*>::iterator it = children.begin(); it != children.end(); ++it) {
            delete *it;
        }
        children.clear();
        childrenIds.clear();
        for (vector<Style*>::iterator it = parents.begin(); it != parents.end(); ++it) {
            delete *it;
        }
        parents.clear();
        parentsIds.clear();
    }

# pragma mark static methods

    void Style::populateFields(const sql::ResultSet* rs, Style* style) {
        style->setId(rs->getInt("id"));
        style->setName(rs->getString("name"));
        style->setREId(rs->getInt("reId"));
        style->setRELabel(rs->getString("reLabel"));
        populateChildrenIds(style);
        populateParentsIds(style);
    }

    void Style::populateChildrenIds(Style* style) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select childId from StyleChildren where parentId = ?");
        ps->setInt(1, style->getId());
        sql::ResultSet *rs = ps->executeQuery();
        while (rs->next()) {
            style->childrenIds.push_back(rs->getInt(1));
        }
        rs->close();
        delete rs;
    }

    void Style::populateParentsIds(Style* style) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select parentId from StyleChildren where childId = ?");
        ps->setInt(1, style->getId());
        sql::ResultSet *rs = ps->executeQuery();
        while (rs->next()) {
            style->parentsIds.push_back(rs->getInt(1));
        }
        rs->close();
        delete rs;
    }

    Style* Style::findById(int id) {
        try {
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

            return style;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Style* Style::findByREId(int reId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles where reId = ?");
            ps->setInt(1, reId);
            sql::ResultSet *rs = ps->executeQuery();
            Style *style = NULL;
            if (rs->next()) {
                style = new Style();
                populateFields(rs, style);
            }
            rs->close();
            delete rs;

            return style;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    dogatech::ResultSetIterator<Style>* Style::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles");
        sql::ResultSet *rs = ps->executeQuery();
        dogatech::ResultSetIterator<Style> *dtrs = new dogatech::ResultSetIterator<Style>(rs);
        return dtrs;
    }

# pragma mark persistence

    bool Style::sync() {
        Style* style = findById(id);
        if (!style) style = findByREId(reId);
        if (!style) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != style->getId()) {
            if (id) {
                cout << "updating style " << id << " id from " << style->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = style->getId();
            }
        }
        if (name.compare(style->getName())  && (!boost::regex_match(name, match1, decimal) || !boost::regex_match(style->getName(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!name.empty()) {
                cout << "updating style " << id << " name from " << style->getName() << " to " << name << endl;
                needsUpdate = true;
            } else {
                name = style->getName();
            }
        }
        if (reId != style->getREId()) {
            if (reId) {
                cout << "updating style " << id << " reId from " << style->getREId() << " to " << reId << endl;
                needsUpdate = true;
            } else {
                reId = style->getREId();
            }
        }
        if (reLabel.compare(style->getRELabel())  && (!boost::regex_match(reLabel, match1, decimal) || !boost::regex_match(style->getRELabel(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!reLabel.empty()) {
                cout << "updating style " << id << " reLabel from " << style->getRELabel() << " to " << reLabel << endl;
                needsUpdate = true;
            } else {
                reLabel = style->getRELabel();
            }
        }
        if (!dogatech::equivalentVectors<int>(childrenIds, style->childrenIds)) {
            if (!dogatech::containsVector<int>(childrenIds, style->childrenIds)) {
                cout << "updating style " << id << " childrenIds" << endl;
                needsUpdate = true;
            }
            dogatech::appendUniqueVector<int>(style->childrenIds, &childrenIds);
            children.clear();
        }
        if (!dogatech::equivalentVectors<int>(parentsIds, style->parentsIds)) {
            if (!dogatech::containsVector<int>(parentsIds, style->parentsIds)) {
                cout << "updating style " << id << " parentsIds" << endl;
                needsUpdate = true;
            }
            dogatech::appendUniqueVector<int>(style->parentsIds, &parentsIds);
            parents.clear();
        }
        return needsUpdate;
    }

    int Style::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Styles set name=?, reId=?, reLabel=? where id=?");
            ps->setString(1, name);
            ps->setInt(2, reId);
            ps->setString(3, reLabel);
            ps->setInt(4, id);
            int result = ps->executeUpdate();
            if (!childrenIds.empty()) {
                ps = MysqlAccess::getInstance().getPreparedStatement("insert ignore into StyleChildren (parentId, childId) values (?, ?)");
                for (vector<int>::const_iterator it = childrenIds.begin(); it != childrenIds.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, *it);
                    ps->executeUpdate();
                }
            }
            if (!parentsIds.empty()) {
                ps = MysqlAccess::getInstance().getPreparedStatement("insert ignore into StyleChildren (childId, parentId) values (?, ?)");
                for (vector<int>::const_iterator it = parentsIds.begin(); it != parentsIds.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, *it);
                    ps->executeUpdate();
                }
            }
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

    int Style::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Styles (name, reId, reLabel) values (?, ?, ?)");
            ps->setString(1, name);
            ps->setInt(2, reId);
            ps->setString(3, reLabel);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save style" << endl;
                return saved;
            } else {
                const int id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted style, but unable to retreive inserted ID." << endl;
                    return saved;
                }
                ps = MysqlAccess::getInstance().getPreparedStatement("insert ignore into StyleChildren (styleId, childId) values (?, ?)");
                for (vector<int>::iterator it = childrenIds.begin(); it != childrenIds.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, *it);
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save child for style " << id << endl;
                    }
                }
                ps = MysqlAccess::getInstance().getPreparedStatement("insert ignore into StyleParents (styleId, parentId) values (?, ?)");
                for (vector<int>::iterator it = parentsIds.begin(); it != parentsIds.end(); ++it) {
                    ps->setInt(1, id);
                    ps->setInt(2, *it);
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save parent for style " << id << endl;
                    }
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

    const int Style::getId() const { return id; }
    void Style::setId(const int id) { this->id = id; }

    const string& Style::getName() const { return name; }
    void Style::setName(const string& name) { this->name = name; }

    const int Style::getREId() const { return reId; }
    void Style::setREId(const int reId) { this->reId = reId; }

    const string& Style::getRELabel() const { return reLabel; }
    void Style::setRELabel(const string& reLabel) { this->reLabel = reLabel; }

    const vector<Style*>& Style::getChildren() {
        if (children.empty() && !childrenIds.empty()) {
            for (vector<int>::const_iterator it = childrenIds.begin(); it != childrenIds.end(); ++it) {
                children.push_back(Style::findById(*it));
            }
        }
        return children;
    }
    void Style::setChildren(const vector<Style*>& children) {
        dogatech::deleteVectorPointers<Style*>(&this->children);
        this->children = children;
        this->childrenIds.clear();
        for (vector<Style*>::const_iterator it = children.begin(); it != children.end(); ++it) {
            this->childrenIds.push_back((*it)->getId());
        }
    }
    void Style::addChildById(int childId) {
        if (std::find(childrenIds.begin(), childrenIds.end(), childId) == childrenIds.end()) {
                childrenIds.push_back(childId);
                if (!children.empty()) children.push_back(Style::findById(childId));
        }
    }
    void Style::removeChildById(int childId) {
        for (vector<Style*>::iterator it = children.begin(); it != children.end(); ++it) {
            if (childId == (*it)->getId()) {
                delete (*it);
                children.erase(it);
            }
        }
        for (vector<int>::iterator it = childrenIds.begin(); it != childrenIds.end(); ++it) {
            if (childId == *it) {
                childrenIds.erase(it);
            }
        }
    }

    const vector<Style*>& Style::getParents() {
        if (parents.empty() && !parentsIds.empty()) {
            for (vector<int>::const_iterator it = parentsIds.begin(); it != parentsIds.end(); ++it) {
                parents.push_back(Style::findById(*it));
            }
        }
        return parents;
    }
    void Style::setParents(const vector<Style*>& parents) {
        dogatech::deleteVectorPointers<Style*>(&this->parents);
        this->parents = parents;
        this->parentsIds.clear();
        for (vector<Style*>::const_iterator it = parents.begin(); it != parents.end(); ++it) {
            this->parentsIds.push_back((*it)->getId());
        }
    }
    void Style::addParentById(int parentId) {
        if (std::find(parentsIds.begin(), parentsIds.end(), parentId) == parentsIds.end()) {
                parentsIds.push_back(parentId);
                if (!parents.empty()) parents.push_back(Style::findById(parentId));
        }
    }
    void Style::removeParentById(int parentId) {
        for (vector<Style*>::iterator it = parents.begin(); it != parents.end(); ++it) {
            if (parentId == (*it)->getId()) {
                delete (*it);
                parents.erase(it);
            }
        }
        for (vector<int>::iterator it = parentsIds.begin(); it != parentsIds.end(); ++it) {
            if (parentId == *it) {
                parentsIds.erase(it);
            }
        }
    }

}
