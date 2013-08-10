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

namespace dogatech {
namespace soulsifter {
    
    int Mix::mixoutCountForRESongId(int outRESongId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select count(*) from Songs s join Mixes m on (s.id = m.outSongId) where s.reSongId = ?");
            ps->setInt(1, outRESongId);
            sql::ResultSet *rs = ps->executeQuery();
            int count = 0;
            if (rs->next()) {
                count = rs->getInt(1);
            }
            rs->close();
            delete rs;
            
            return count;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }
    
}
}