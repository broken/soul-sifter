//
//  MysqlAccess.h
//  soul-sifter
//
//  Created by Robby Neale on 11/11/12.
//
//  TODO make this derived from a generic version

#ifndef __soul_sifter__MysqlAccess__
#define __soul_sifter__MysqlAccess__

#include <map>
#include <string>

#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class Connection;
class Driver;

namespace dogatech {
namespace soulsifter {
    
    // public helper methods for working with times & a db
    time_t timeFromString(const std::string& str);
    std::string stringFromTime(const time_t time);

class MysqlAccess {
public:
    ~MysqlAccess();
    
    static MysqlAccess& getInstance() {
        static MysqlAccess instance;  // guaranteed to be destroyed
        // instantiated on first use
        return instance;
    }

    sql::Connection *getConnection() {
        return connection;
    }
    
    sql::PreparedStatement* getPreparedStatement(std::string query);
    
    const int getLastInsertId();
    
private:
    MysqlAccess();
    MysqlAccess(MysqlAccess const&);
    void operator=(MysqlAccess const&);
    
    bool connect();
    bool disconnect();
    sql::Driver *driver;
    sql::Connection *connection;
    std::map<std::string, sql::PreparedStatement*> preparedStatements;
};
  
}
}

#endif /* defined(__soul_sifter__MysqlAccess__) */
