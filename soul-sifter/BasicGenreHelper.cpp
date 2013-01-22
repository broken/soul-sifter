//
//  BasicGenreHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/21/13.
//
//

#include "BasicGenre.h"

#include <string>
#include <vector>

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"


namespace soulsifter {
    
    const BasicGenre* BasicGenre::findByFilepath(const string& filepath) {
        unsigned long pos = filepath.find("/mp3/");
        if (pos != string::npos) {
            pos += 5;
            unsigned long pos2 = filepath.find("/", pos);
            return findByName(filepath.substr(pos, pos2-pos));
        }
        pos = filepath.find("/staging/");
        if (pos != string::npos) {
            pos += 9;
            unsigned long pos2 = filepath.find("/", pos);
            return findByName(filepath.substr(pos, pos2-pos));
        }
        return NULL;
    }
    
    void BasicGenre::findAll(const vector<const BasicGenre*>** genresPtr) {
        static vector<const BasicGenre*> basicGenres;
        if (basicGenres.size() == 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres");
            sql::ResultSet *rs = ps->executeQuery();
            while (rs->next()) {
                for (vector<const BasicGenre*>::iterator it = basicGenres.begin(); it != basicGenres.end(); ++it) {
                    if ((*it)->id == rs->getInt("id")) {
                        continue;
                    }
                }
                BasicGenre *genre = new BasicGenre();
                populateFields(rs, genre);
                basicGenres.push_back(genre);
            }
            rs->close();
            delete rs;
        }
        (*genresPtr) = &basicGenres;
    }
    
}