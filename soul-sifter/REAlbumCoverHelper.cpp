//
//  REAlbumCoverHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/22/13.
//
//

#include "REAlbumCover.h"

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"

namespace soulsifter {
    
# pragma mark RESongIterator
    
    REAlbumCover::REAlbumCoverIterator::REAlbumCoverIterator(sql::ResultSet* resultset) :
    rs(resultset) {
    }
    
    REAlbumCover::REAlbumCoverIterator::~REAlbumCoverIterator() {
        delete rs;
    }
    
    bool REAlbumCover::REAlbumCoverIterator::next(REAlbumCover* albumcover) {
        if (rs->next()) {
            populateFields(rs, albumcover);
            return true;
        } else {
            return false;
        }
    }
    
#pragma mark static methods
    
    REAlbumCover::REAlbumCoverIterator* REAlbumCover::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from REAlbumCovers");
        sql::ResultSet *rs = ps->executeQuery();
        REAlbumCoverIterator *it = new REAlbumCoverIterator(rs);
        return it;
    }
}