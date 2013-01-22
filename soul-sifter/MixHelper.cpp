//
//  MixHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/22/13.
//
//

#include "Mix.h"

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"

namespace soulsifter {
    
    Mix* Mix::findBySongIds(const int outSongId, const int inSongId) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Mixes where outSongId = ? and inSongId = ?");
        ps->setInt(1, outSongId);
        ps->setInt(2, inSongId);
        sql::ResultSet *rs = ps->executeQuery();
        Mix *mix = NULL;
        if (rs->next()) {
            mix = new Mix();
            populateFields(rs, mix);
        }
        rs->close();
        delete rs;
        return mix;
    }
    
    Mix::MixResultSet* Mix::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Mixes");
        sql::ResultSet *rs = ps->executeQuery();
        MixResultSet *mrs = new MixResultSet(rs);
        return mrs;
    }
    
# pragma mark MixResultSet
    
    Mix::MixResultSet::MixResultSet(sql::ResultSet* resultset) :
    rs(resultset) {
    }
    
    Mix::MixResultSet::~MixResultSet() {
        delete rs;
    }
    
    bool Mix::MixResultSet::next(Mix* mix) {
        if (rs->next()) {
            populateFields(rs, mix);
            return true;
        } else {
            return false;
        }
    }
    
}