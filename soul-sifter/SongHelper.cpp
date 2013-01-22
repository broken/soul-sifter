//
//  SongHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/22/13.
//
//

#include "Song.h"

#include <sstream>

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "Album.h"
#include "MysqlAccess.h"
#include "RESong.h"

namespace soulsifter {
    
    Song::Song(RESong* song) :
    id(0),
    artist(song->getArtist()),
    track(song->getTrack()),
    title(song->getTitle()),
    remix(song->getRemix()),
    featuring(song->getFeaturing()),
    filepath(song->getFilename()),
    reSongId(song->getUniqueId()),
    reSong(song),
    styles(),
    rating(song->getRating()),
    albumId(0),
    album(NULL),
    dateAdded(timeFromeString(song->getDateAdded())),
    comments(song->getComments()),
    trashed(!song->getDisabled().compare("yes")) {
        
        // styles
        const vector<Style*>* allStyles;
        Style::findAllSorted(&allStyles);
        unsigned long pos = song->getStylesBitmask().find('1', 0);
        while (pos != string::npos) {
            styles.push_back(allStyles->at(pos));
            pos = song->getStylesBitmask().find('1', ++pos);
        }
        
        // album
        album = Album::findByName(song->getAlbum());
        if (!album) album = new Album();
        album->setName(song->getAlbum());
        album->setLabel(song->getLabel());
        album->setCatalogId(song->getCatalogId());
        albumId = album->getId();
        // release dates
        string releaseDate = song->getReleaseDate();
        if (releaseDate.length() >=4) {
            album->setReleaseDateYear(atoi(releaseDate.substr(0,4).c_str()));
            if (releaseDate.length() >= 6) {
                album->setReleaseDateMonth(atoi(releaseDate.substr(4,2).c_str()));
                if (releaseDate.length() >= 8) {
                    album->setReleaseDateDay(atoi(releaseDate.substr(6,2).c_str()));
                }
            }
        }
        // basic genre
        const BasicGenre *genre = BasicGenre::findByFilepath(song->getFilename());
        if (genre)
            album->setBasicGenre(genre);
        // date added
        dateAdded = timeFromeString(song->getDateAdded());
    }
    
    void Song::findSongsByStyle(const Style& style, vector<Song*>** songsPtr) {
        vector<Song*>* songs = new vector<Song*>;
        (*songsPtr) = songs;
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select s.* from SongStyles ss join Songs s on ss.songId = s.id join RESongs re on re.unique_id = s.reSongId where ss.styleId = ? order by re.songId");
        ps->setInt(1, style.getId());
        sql::ResultSet *rs = ps->executeQuery();
        while (rs->next()) {
            Song* song = new Song();
            populateFields(rs, song);
            songs->push_back(song);
        }
        rs->close();
        delete rs;
    }
    
    const string Song::reAlbum() const {
        if (!getAlbum()->getName().empty()) {
            return getAlbum()->getName();
        } else {
            stringstream ss;
            ss << title;
            if (!remix.empty()) {
                ss << " " << remix;
            }
            return ss.str();
        }
    }
    
    const string Song::getDateAddedString() const { return stringFromTime(dateAdded); }
    void Song::setDateAddedToNow() { dateAdded = time(0); }
}