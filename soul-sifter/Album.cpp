//
//  Album.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/9/12.
//
//

#include "Album.h"

#include <sstream>
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
    
#pragma mark initialization
    
    Album::Album() :
    id(0),
    name(),
    coverFilepath(),
    mixed(false),
    label(),
    catalogId(),
    releaseDateYear(0),
    releaseDateMonth(0),
    releaseDateDay(0),
    basicGenreId(0),
    basicGenre(NULL) {
    }
    
    Album::~Album() {
    }
    
    void Album::clear() {
        id = 0;
        name.clear();
        coverFilepath.clear();
        mixed = false;
        label.clear();
        catalogId.clear();
        releaseDateYear = 0;
        releaseDateMonth = 0;
        releaseDateDay = 0;
        basicGenreId = 0;
        basicGenre = NULL;
    }
    
#pragma mark static methods
    
    void Album::populateFields(const sql::ResultSet* rs, Album* album) {
        album->setId(rs->getInt("id"));
        album->setName(rs->getString("name"));
        album->setCoverFilepath(rs->getString("coverFilepath"));
        album->setMixed(rs->getBoolean("mixed"));
        album->setLabel(rs->getString("label"));
        album->setCatalogId(rs->getString("catalogId"));
        album->setReleaseDateYear(rs->getInt("releaseDateYear"));
        album->setReleaseDateMonth(rs->getInt("releaseDateMonth"));
        album->setReleaseDateDay(rs->getInt("releaseDateDay"));
        album->setBasicGenreId(rs->getInt("basicGenreId"));
    }
    
    Album* Album::findById(const int id) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where id = ?");
        ps->setInt(1, id);
        sql::ResultSet *rs = ps->executeQuery();
        Album *album = NULL;
        if (rs->next()) {
            album = new Album();
            populateFields(rs, album);
        }
        rs->close();
        delete rs;
        
        return album;
    }
    
    Album* Album::findByName(const string& name) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where name = ?");
        ps->setString(1, name);
        sql::ResultSet *rs = ps->executeQuery();
        Album *album = NULL;
        if (rs->next()) {
            album = new Album();
            populateFields(rs, album);
        }
        rs->close();
        delete rs;
        
        return album;
    }
    
    Album* Album::findByCoverFilepath(const string& filepath) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where coverFilepath = ?");
        ps->setString(1, filepath);
        sql::ResultSet *rs = ps->executeQuery();
        Album *album = NULL;
        if (rs->next()) {
            album = new Album();
            populateFields(rs, album);
        }
        rs->close();
        delete rs;
        
        return album;
    }
    
#pragma mark persistence
    
    bool Album::sync() {
        try {
            Album* album = findById(id);
            if (!album) {
                return true;
            }
            
            // check fields
            bool needsUpdate = false;
            if (id != album->getId()) {
                needsUpdate = true;
                if (id) {
                    cout << "updating album's id from " << album->getId() << " to " << id << endl;
                } else {
                    id = album->getId();
                }
            }
            if (name.compare(album->getName())) {
                needsUpdate = true;
                if (!name.empty()) {
                    cout << "updating album name from " << album->getName() << " to " << name << endl;
                } else {
                    name = album->getName();
                }
            }
            if (coverFilepath.compare(album->getCoverFilepath())) {
                needsUpdate = true;
                if (!coverFilepath.empty()) {
                    cout << "updating album coverFilepath from " << album->getCoverFilepath() << " to " << coverFilepath << endl;
                } else {
                    coverFilepath = album->getCoverFilepath();
                }
            }
            if (mixed != album->getMixed()) {
                needsUpdate = true;
                if (mixed) {
                    cout << "updating album is mixed from " << album->getMixed() << " to " << mixed << endl;
                } else {
                    mixed = album->getMixed();
                }
            }
            if (label.compare(album->getLabel())) {
                needsUpdate = true;
                if (!label.empty()) {
                    cout << "updating album label from " << album->getLabel() << " to " << label << endl;
                } else {
                    label = album->getLabel();
                }
            }
            if (catalogId.compare(album->getCatalogId())) {
                needsUpdate = true;
                if (!catalogId.empty()) {
                    cout << "updating album catalogId from " << album->getCatalogId() << " to " << catalogId << endl;
                } else {
                    catalogId = album->getCatalogId();
                }
            }
            if (releaseDateYear != album->getReleaseDateYear()) {
                needsUpdate = true;
                if (releaseDateYear) {
                    cout << "updating album's releaseDateYear from " << album->getReleaseDateYear() << " to " << releaseDateYear << endl;
                } else {
                    releaseDateYear = album->getReleaseDateYear();
                }
            }
            if (releaseDateMonth != album->getReleaseDateMonth()) {
                needsUpdate = true;
                if (releaseDateMonth) {
                    cout << "updating album's releaseDateMonth from " << album->getReleaseDateMonth() << " to " << releaseDateMonth << endl;
                } else {
                    releaseDateMonth = album->getReleaseDateMonth();
                }
            }
            if (releaseDateDay != album->getReleaseDateDay()) {
                needsUpdate = true;
                if (releaseDateDay) {
                    cout << "updating album's releaseDateDay from " << album->getReleaseDateDay() << " to " << releaseDateDay << endl;
                } else {
                    releaseDateDay = album->getReleaseDateDay();
                }
            }
            if (basicGenreId != album->getBasicGenreId()) {
                needsUpdate = true;
                if (basicGenreId) {
                    cout << "updating album's basicGenreId from " << album->getBasicGenreId() << " to " << basicGenreId << endl;
                } else {
                    basicGenreId = album->getBasicGenreId();
                }
            }
            return needsUpdate;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << std::endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
            return false;
        }
    }
    
    bool Album::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Albums set name=?, coverFilepath=?, mixed=?, label=?, catalogId=?, releaseDateYear=?, releaseDateMonth=?, releaseDateDay=?, basicGenreId=? where id=?");
            ps->setString(1, name);
            ps->setString(2, coverFilepath);
            ps->setBoolean(3, mixed);
            ps->setString(4, label);
            ps->setString(5, catalogId);
            ps->setInt(6, releaseDateYear);
            ps->setInt(7, releaseDateMonth);
            ps->setInt(8, releaseDateDay);
            ps->setInt(9, basicGenreId);
            ps->setInt(10, id);
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
    
    int Album::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Albums (name, coverFilepath, mixed, label, catalogId, releaseDateYear, releaseDateMonth, releaseDateDay, basicGenreId) values (?,?,?,?,?,?,?,?,?)");
            ps->setString(1, name);
            ps->setString(2, coverFilepath);
            ps->setBoolean(3, mixed);
            ps->setString(4, label);
            ps->setString(5, catalogId);
            ps->setInt(6, releaseDateYear);
            ps->setInt(7, releaseDateMonth);
            ps->setInt(8, releaseDateDay);
            ps->setInt(9, basicGenreId);
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
    
#pragma mark accessors
    
    const int Album::getId() const { return id; }
    void Album::setId(const int id) { this->id = id; }
    
    const string& Album::getName() const { return name; }
    void Album::setName(const string& name) { this->name = name; }
    
    const string& Album::getCoverFilepath() const { return coverFilepath; }
    void Album::setCoverFilepath(const string& coverFilepath) { this->coverFilepath = coverFilepath; }
    
    const bool Album::getMixed() const { return mixed; }
    void Album::setMixed(const bool mixed) { this->mixed = mixed; }
    
    const string& Album::getLabel() const { return label; }
    void Album::setLabel(const string& label) { this->label = label; }
    
    const string& Album::getCatalogId() const { return catalogId; }
    void Album::setCatalogId(const string& catalogId) { this->catalogId = catalogId; }
    
    const int Album::getReleaseDateYear() const { return releaseDateYear; }
    void Album::setReleaseDateYear(const int releaseDateYear) { this->releaseDateYear = releaseDateYear; }
    
    const int Album::getReleaseDateMonth() const { return releaseDateMonth; }
    void Album::setReleaseDateMonth(const int releaseDateMonth) { this->releaseDateMonth = releaseDateMonth; }
    
    const int Album::getReleaseDateDay() const { return releaseDateDay; }
    void Album::setReleaseDateDay(const int releaseDateDay) { this->releaseDateDay = releaseDateDay; }
    
    const int Album::getBasicGenreId() const { return basicGenreId; }
    void Album::setBasicGenreId(const int basicGenreId) { this->basicGenreId = basicGenreId; }
    
    const BasicGenre* Album::getBasicGenre() const {
        return basicGenre ? basicGenre : BasicGenre::findById(basicGenreId);
    }
    void Album::setBasicGenre(const BasicGenre* basicGenre) {
        this->basicGenreId = basicGenre->getId();
        this->basicGenre = basicGenre;
    }
    
}
