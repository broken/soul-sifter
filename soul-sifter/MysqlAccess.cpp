//
//  MysqlAccess.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/11/12.
//
//

#include "MysqlAccess.h"

#include <iostream>
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

using namespace sql;

MysqlAccess::MysqlAccess() :
driver(0),
connection(0) {
}

void MysqlAccess::handleException(const SQLException& e) {
    std::cout << "ERROR: SQLException in " << __FILE__;
    std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
    std::cout << "ERROR: " << e.what();
    std::cout << " (MySQL error code: " << e.getErrorCode();
    std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
    
    if (e.getErrorCode() == 1047) {
        /*
         Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
         Message: Unknown command
         */
        std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
        std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
    }
}

bool MysqlAccess::connect() {
    /* initiate url, user, password and database variables */
    const std::string url("localhost");
    const std::string user("ss");
    const std::string password("pw");
    const std::string database("music");
    
    try {
        driver = get_driver_instance();
        
        /* create a database connection using the Driver */
        connection = driver->connect(url, user, password);
        connection->setAutoCommit(1);
        connection->setSchema(database);
    } catch (SQLException &e) {
        handleException(e);
	}
}
    
bool MysqlAccess::disconnect() {
    try {
        connection->close();
        delete connection;
    } catch (SQLException &e) {
        handleException(e);
    }
}

Style* MysqlAccess::getStyle() {
    try {
        /* create a statement object */
        stmt = connection->createStatement();
        
        /* run a query which returns exactly one result set */
        res = stmt->executeQuery ("select * from styles where id = XXX");  // todo
        
        /* retrieve the data from the result set and display on stdout */
        //retrieve_data_and_print(res, NUMOFFSET, 1, string("style"));
        
        /* retrieve and display the result set metadata */
        //retrieve_rsmetadata_and_print (res);
    } catch (SQLException &e) {
        handleException(e);
    }
    return NULL;
}

bool MysqlAccess::updateStyle(const Style& style) {
    try {
        Style* style = getStyle();
    } catch (SQLException &e) {
        handleException(e);
    }
    return false;
}

bool MysqlAccess::saveStyle(const Style& style) {
    try {
        /* insert couple of rows of data into City table using Prepared Statements */
        prep_stmt = connection->prepareStatement ("insert into styles (name) values (?)");
    
        prep_stmt->setString (1, style.name);
        int updatecount = prep_stmt->executeUpdate();
        connection->commit();
    
        /* re-use result set object */
        res = NULL;
        res = stmt -> executeQuery ("SELECT * FROM City");
    
        /* retrieve the data from the result set and display on stdout */
        //retrieve_data_and_print (res, COLNAME, 1, string ("CityName"));
    
        std::cout << "Cleaning up the resources .." << std::endl;
        
        /* Clean up */
        delete res;
        delete stmt;
        delete prep_stmt;
        connection->close();
        delete connection;
    
	} catch (SQLException &e) {
		handleException(e);
	}
    return false;
}
