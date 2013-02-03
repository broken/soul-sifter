//
//  RESongHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/22/13.
//
//

#include "RESong.h"

#include <sstream>

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"
#include "Style.h"

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
    
    void RESong::getStylesFromBitmask(vector<Style*>** styles) {
        *styles = new vector<Style*>();
        vector<Style*>* allStyles;
        Style::findAllSorted(&allStyles);
        
        unsigned long pos = getStylesBitmask().find('1', 0);
        while (pos != string::npos) {
            (*styles)->push_back(allStyles->at(pos));
            pos = getStylesBitmask().find('1', ++pos);
        }
        
        while (!allStyles->empty()) delete allStyles->back(), allStyles->pop_back();
    }
    
    void RESong::setStylesBitmaskFromDb() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select count(*) from Styles");
        sql::ResultSet *rs = ps->executeQuery();
        int stylesCount = 0;
        if (rs->next()) {
            stylesCount = rs->getInt(1);
        } else {
            cerr << "Unable to get total count of styles" << endl;
            return;
        }
        rs->close();
        delete rs;
        
        ps = MysqlAccess::getInstance().getPreparedStatement("set @n=0");
        if (!ps->execute())
            cerr << "Unable to set count var" << endl;
        ps = MysqlAccess::getInstance().getPreparedStatement("select os.n from songs s join songstyles ss on s.id=ss.songid join (select @n:=1+@n n, id from styles order by relabel) os on ss.styleid=os.id where s.resongid=? order by os.n");
        ps->setInt(1, id);
        rs = ps->executeQuery();
        int nextStyleBit = -1;
        if (rs->next())
            nextStyleBit = rs->getInt(1);
        stringstream ss;
        for (int i = 0; i < stylesCount; ++i) {
            if (i == nextStyleBit - 1) {
                ss << "1";
                if (rs->next())
                    nextStyleBit = rs->getInt(1);
            } else {
                ss << "0";
            }
        }
        rs->close();
        delete rs;
        
        setStylesBitmask(ss.str());
    }
    
    // TODO need to fix - is broken
    void RESong::setStylesBitmask(const vector<Style*>& styles) {
        vector<Style*>* allStyles;
        Style::findAllSorted(&allStyles);
        stringstream ss;
        for (vector<Style*>::iterator it = allStyles->begin(); it != allStyles->end(); ++it) {
            bool inStyles = false;
            for (vector<Style*>::const_iterator it2 = styles.begin(); it2 != styles.end(); ++it2) {
                if ((*it2)->getId() == (*it2)->getId()) {
                    inStyles = true;
                    break;
                }
            }
            ss << (inStyles ? "1" : "0");
        }
        stylesBitmask = ss.str();
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