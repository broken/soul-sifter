//
//  MysqlAccess.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/11/12.
//
//

#include "MysqlAccess.h"

#include <iostream>
#include <map>
#include <string>

/* MySQL Connector/C++ specific headers */
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <mysql_driver.h>

namespace soulsifter {
    
# pragma mark public helpers
    
    time_t timeFromString(const std::string& str) {
        struct tm dt;
        memset(&dt, 0, sizeof(dt));
        strptime(str.c_str(), "%Y-%m-%d %X", &dt);
        return mktime(&dt);
    }
    
    std::string stringFromTime(const time_t time) {
        struct tm dt = *localtime(&time);
        char buffer[80];
        memset(buffer, 0, 80);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %X %Z", &dt);
        std::string str(buffer);
        return str;
    }

# pragma mark initialization

MysqlAccess::MysqlAccess() :
driver(0),
connection(0),
preparedStatements() {
    connect();
}

MysqlAccess::~MysqlAccess() {
    disconnect();
}

# pragma mark connecting

bool MysqlAccess::connect() {
    // initiate url, user, password and database variables
    const std::string url("localhost");
    const std::string user("ss");
    const std::string password("pw");
    const std::string database("music");
    
    try {
        driver = get_driver_instance();
        
        // create a database connection using the Driver
        connection = driver->connect(url, user, password);
        connection->setAutoCommit(1);
        connection->setSchema(database);
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
	}
    return true;
}
    
bool MysqlAccess::disconnect() {
    try {
        connection->close();
        delete connection;
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
    }
    return true;
}

sql::PreparedStatement* MysqlAccess::getPreparedStatement(std::string query) {
    try {
        sql::PreparedStatement *ps;
        std::map<std::string, sql::PreparedStatement*>::iterator it = preparedStatements.find(query);
        if (it == preparedStatements.end()) {
            ps = connection->prepareStatement(query);
            preparedStatements.insert(std::pair<std::string, sql::PreparedStatement*>(query, ps));
        } else {
            ps = it->second;
        }
        return ps;
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        throw e;
    }
}

const int MysqlAccess::getLastInsertId() {
    try {
        sql::PreparedStatement *ps = getPreparedStatement("select LAST_INSERT_ID()");
        sql::ResultSet *rs = ps->executeQuery();
        int id = 0;
        if (rs->next()) {
            id = rs->getInt(1);
        }
        rs->close();
        delete rs;
        return id;
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        throw e;
    }
}
    
}
