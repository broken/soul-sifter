//
//  RESongHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/22/13.
//
//

#include "RESong.h"

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"

namespace soulsifter {
    
    RESong::RESong(const Song& song) :
    unique_id(0),
    songid_winfo(),
    songid(),
    shortid(),
    shortid_winfo(),
    artist(song.getArtist()),
    album(song.reAlbum()),
    track(song.getTrack()),
    title(song.getTitle()),
    time(),
    time_signature(),
    filename(song.getFilepath()),
    digital_only(),
    compilation(),
    key_start(),
    key_accuracy(0),
    bpm_start(),
    bpm_accuracy(0),
    rating(song.getRating()),
    date_added(song.getDateAddedString()),
    catalog_id(song.getAlbum()->getCatalogId()),
    label(song.getAlbum()->getLabel()),
    remix(song.getRemix()),
    num_plays(0),
    comments(song.getComments()),
    release_date(song.getAlbum()->reReleaseDate()),
    featuring(song.getFeaturing()),
    key_end(),
    disabled(song.getTrashed() ? "yes" : "no"),
    bpm_end(),
    beat_intensity(0),
    replay_gain(),
    styles_bitmask() {
    }
    
    RESong::RESongIterator* RESong::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select re.*, count(m.outSongId) as cnt from RESongs re join Songs s on re.unique_id = s.reSongId left join Mixes m on s.id = m.outSongId group by re.unique_id order by re.songId");
        sql::ResultSet *rs = ps->executeQuery();
        RESongIterator *it = new RESongIterator(rs);
        return it;
    }
    
    const int RESong::maxREId() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select max(unique_id) from RESongs");
        sql::ResultSet *rs = ps->executeQuery();
        int max = 0;
        if (rs->next())
            max = rs->getInt(1);
        rs->close();
        delete rs;
        return max;
    }
    
# pragma mark RESongIterator
    
    RESong::RESongIterator::RESongIterator(sql::ResultSet* resultset) :
    rs(resultset),
    mixoutCount(0) {
    }
    
    RESong::RESongIterator::~RESongIterator() {
        rs->close();
        delete rs;
    }
    
    bool RESong::RESongIterator::next(RESong* song) {
        if (rs->next()) {
            populateFields(rs, song);
            mixoutCount = rs->getInt("cnt");
            return true;
        } else {
            return false;
        }
    }
    
    const int RESong::RESongIterator::getMixoutCountForCurrentSong() const { return mixoutCount; }
}