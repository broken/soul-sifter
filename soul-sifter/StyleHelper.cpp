//
//  StyleHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/22/13.
//
//

#include "Style.h"

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"

namespace soulsifter {
    
# pragma mark helpers
    
    namespace {
        
        struct lessThanKey {
            inline bool operator()(const Style* v1, const Style* v2) {
                return (*v1) < (*v2);
            }
        };
        
    }
    
# pragma mark operator overrides
    
    bool Style::operator<(const Style& style) const {
        return name.compare(style.getName()) < 0;
    }
    
    bool Style::operator>(const Style& style) const {
        return name.compare(style.getName()) > 0;
    }
    
# pragma mark static methods
    
    void Style::findAll(vector<Style*>** stylesPtr) {
        static vector<Style*> styles;
        if (styles.size() == 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from Styles");
            sql::ResultSet *rs = ps->executeQuery();
            while (rs->next()) {
                for (vector<Style*>::iterator it = styles.begin(); it != styles.end(); ++it) {
                    if ((*it)->id == rs->getInt("id")) {
                        continue;
                    }
                }
                Style *style = new Style();
                populateFields(rs, style);
                styles.push_back(style);
            }
            rs->close();
            delete rs;
        }
        (*stylesPtr) = &styles;
    }
    
    void Style::findAllSorted(vector<Style*>** stylesPtr) {
        findAll(stylesPtr);
        vector<Style*>* styles = *stylesPtr;
        sort(styles->begin(), styles->end(), lessThanKey());
    }
}