//
//  MysqlAccess.h
//  soul-sifter
//
//  Created by Robby Neale on 11/11/12.
//
//

#ifndef __soul_sifter__MysqlAccess__
#define __soul_sifter__MysqlAccess__

#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>

#include "Style.h"

class Connection;
class Driver;
class PreparedStatement;
class ResultSet;
class Savepoint;
class Statement;

class MysqlAccess {
public:
    MysqlAccess();
    
    bool connect();
    bool disconnect();
    
    Style* getStyle();
    bool updateStyle(const Style& style);
    bool saveStyle(const Style& style);
private:
    sql::Driver *driver;
    sql::Connection *connection;
    
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *prep_stmt;
    sql::Savepoint *savept;
    
    void handleException(const sql::SQLException& e);
};

#endif /* defined(__soul_sifter__MysqlAccess__) */
