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