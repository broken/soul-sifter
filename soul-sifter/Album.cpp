//
//  Album.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Album.h"

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

    Album::Album() :
    id(0),
    name(),
    artist(),
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

    Album::Album(const Album& album) :
    id(album.getId()),
    name(album.getName()),
    artist(album.getArtist()),
    coverFilepath(album.getCoverFilepath()),
    mixed(album.getMixed()),
    label(album.getLabel()),
    catalogId(album.getCatalogId()),
    releaseDateYear(album.getReleaseDateYear()),
    releaseDateMonth(album.getReleaseDateMonth()),
    releaseDateDay(album.getReleaseDateDay()),
    basicGenreId(album.getBasicGenreId()),
    basicGenre(NULL) {
    }

    void Album::operator=(const Album& album) {
        id = album.getId();
        name = album.getName();
        artist = album.getArtist();
        coverFilepath = album.getCoverFilepath();
        mixed = album.getMixed();
        label = album.getLabel();
        catalogId = album.getCatalogId();
        releaseDateYear = album.getReleaseDateYear();
        releaseDateMonth = album.getReleaseDateMonth();
        releaseDateDay = album.getReleaseDateDay();
        basicGenreId = album.getBasicGenreId();
        basicGenre = NULL;
    }

    Album::~Album() {
        delete basicGenre;
        basicGenre = NULL;
    }

    void Album::clear() {
        id = 0;
        name.clear();
        artist.clear();
        coverFilepath.clear();
        mixed = false;
        label.clear();
        catalogId.clear();
        releaseDateYear = 0;
        releaseDateMonth = 0;
        releaseDateDay = 0;
        basicGenreId = 0;
        delete basicGenre;
        basicGenre = NULL;
    }

# pragma mark static methods

    void Album::populateFields(const sql::ResultSet* rs, Album* album) {
        album->setId(rs->getInt("id"));
        album->setName(rs->getString("name"));
        album->setArtist(rs->getString("artist"));
        album->setCoverFilepath(rs->getString("coverFilepath"));
        album->setMixed(rs->getBoolean("mixed"));
        album->setLabel(rs->getString("label"));
        album->setCatalogId(rs->getString("catalogId"));
        album->setReleaseDateYear(rs->getInt("releaseDateYear"));
        album->setReleaseDateMonth(rs->getInt("releaseDateMonth"));
        album->setReleaseDateDay(rs->getInt("releaseDateDay"));
        album->setBasicGenreId(rs->getInt("basicGenreId"));
    }

    Album* Album::findById(int id) {
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

    Album* Album::findByCoverFilepath(const string& coverFilepath) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where coverFilepath = ?");
        ps->setString(1, coverFilepath);
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

    Album* Album::findByNameAndArtist(const string& name, const string& artist) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Albums where name = ? and artist = ?");
        ps->setString(1, name);
        ps->setString(1, artist);
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

# pragma mark persistence

    bool Album::sync() {
        Album* album = findById(id);
        if (!album) album = findByNameAndArtist(name, artist);
        if (!album) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        if (id != album->getId()) {
            if (id) {
                cout << "updating album's id from " << album->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = album->getId();
            }
        }
        if (name.compare(album->getName())) {
            if (!name.empty()) {
                cout << "updating album name from " << album->getName() << " to " << name << endl;
                needsUpdate = true;
            } else {
                name = album->getName();
            }
        }
        if (artist.compare(album->getArtist())) {
            if (!artist.empty()) {
                cout << "updating album artist from " << album->getArtist() << " to " << artist << endl;
                needsUpdate = true;
            } else {
                artist = album->getArtist();
            }
        }
        if (coverFilepath.compare(album->getCoverFilepath())) {
            if (!coverFilepath.empty()) {
                cout << "updating album coverFilepath from " << album->getCoverFilepath() << " to " << coverFilepath << endl;
                needsUpdate = true;
            } else {
                coverFilepath = album->getCoverFilepath();
            }
        }
        if (mixed != album->getMixed()) {
            if (mixed) {
                cout << "updating album's mixed from " << album->getMixed() << " to " << mixed << endl;
                needsUpdate = true;
            } else {
                mixed = album->getMixed();
            }
        }
        if (label.compare(album->getLabel())) {
            if (!label.empty()) {
                cout << "updating album label from " << album->getLabel() << " to " << label << endl;
                needsUpdate = true;
            } else {
                label = album->getLabel();
            }
        }
        if (catalogId.compare(album->getCatalogId())) {
            if (!catalogId.empty()) {
                cout << "updating album catalogId from " << album->getCatalogId() << " to " << catalogId << endl;
                needsUpdate = true;
            } else {
                catalogId = album->getCatalogId();
            }
        }
        if (releaseDateYear != album->getReleaseDateYear()) {
            if (releaseDateYear) {
                cout << "updating album's releaseDateYear from " << album->getReleaseDateYear() << " to " << releaseDateYear << endl;
                needsUpdate = true;
            } else {
                releaseDateYear = album->getReleaseDateYear();
            }
        }
        if (releaseDateMonth != album->getReleaseDateMonth()) {
            if (releaseDateMonth) {
                cout << "updating album's releaseDateMonth from " << album->getReleaseDateMonth() << " to " << releaseDateMonth << endl;
                needsUpdate = true;
            } else {
                releaseDateMonth = album->getReleaseDateMonth();
            }
        }
        if (releaseDateDay != album->getReleaseDateDay()) {
            if (releaseDateDay) {
                cout << "updating album's releaseDateDay from " << album->getReleaseDateDay() << " to " << releaseDateDay << endl;
                needsUpdate = true;
            } else {
                releaseDateDay = album->getReleaseDateDay();
            }
        }
        if (basicGenreId != album->getBasicGenreId()) {
            if (basicGenreId) {
                cout << "updating album's basicGenreId from " << album->getBasicGenreId() << " to " << basicGenreId << endl;
                needsUpdate = true;
            } else {
                basicGenreId = album->getBasicGenreId();
            }
        }
        return needsUpdate;
    }

    int Album::update() {
        try {
            if (basicGenre && basicGenre->sync()) {
                basicGenre->update();
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Albums set name=?, artist=?, coverFilepath=?, mixed=?, label=?, catalogId=?, releaseDateYear=?, releaseDateMonth=?, releaseDateDay=?, basicGenreId=? where id=?");
            ps->setString(1, name);
            ps->setString(2, artist);
            ps->setString(3, coverFilepath);
            ps->setBoolean(4, mixed);
            ps->setString(5, label);
            ps->setString(6, catalogId);
            ps->setInt(7, releaseDateYear);
            ps->setInt(8, releaseDateMonth);
            ps->setInt(9, releaseDateDay);
            ps->setInt(10, basicGenreId);
            ps->setInt(11, id);
            int result = ps->executeUpdate();
            return result;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            return 0;
        }
    }

    int Album::save() {
        try {
            if (basicGenre && (!basicGenre->getId() || !BasicGenre::findById(basicGenre->getId()))) {
                if (basicGenre->save()) {
                    if (basicGenre->getId()) {
                        basicGenreId = basicGenre->getId();
                    } else {
                        basicGenreId = MysqlAccess::getInstance().getLastInsertId();
                        basicGenre->setId(basicGenreId);
                    }
                } else {
                    cerr << "Unable to save basicGenre" << endl;
                }
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Albums (name, artist, coverFilepath, mixed, label, catalogId, releaseDateYear, releaseDateMonth, releaseDateDay, basicGenreId) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            ps->setString(1, name);
            ps->setString(2, artist);
            ps->setString(3, coverFilepath);
            ps->setBoolean(4, mixed);
            ps->setString(5, label);
            ps->setString(6, catalogId);
            ps->setInt(7, releaseDateYear);
            ps->setInt(8, releaseDateMonth);
            ps->setInt(9, releaseDateDay);
            ps->setInt(10, basicGenreId);
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

    const int Album::getId() const { return id; }
    void Album::setId(const int id) { this->id = id; }

    const string& Album::getName() const { return name; }
    void Album::setName(const string& name) { this->name = name; }

    const string& Album::getArtist() const { return artist; }
    void Album::setArtist(const string& artist) { this->artist = artist; }

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
    void Album::setBasicGenreId(const int basicGenreId) {
        this->basicGenreId = basicGenreId;
        delete basicGenre;
        basicGenre = NULL;
    }

    BasicGenre* Album::getBasicGenre() const {
        if (!basicGenre && basicGenreId)
            return BasicGenre::findById(basicGenreId);
        return basicGenre;
    }
    void Album::setBasicGenre(const BasicGenre& basicGenre) {
        this->basicGenreId = basicGenre.getId();
        delete this->basicGenre;
        this->basicGenre = new BasicGenre(basicGenre);
    }

}
