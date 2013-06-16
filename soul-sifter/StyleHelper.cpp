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
        
        struct reIdLessThanKey {
            inline bool operator()(const Style* v1, const Style* v2) {
                return v1->getREId() < v2->getREId();
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
    
    void Style::findAllSortedByName(vector<Style*>** stylesPtr) {
        vector<Style*>* styles = Style::findAll()->toVector();
        sort(styles->begin(), styles->end(), lessThanKey());
    }
    
    void Style::findAllSortedByREId(vector<Style*>** stylesPtr) {
        vector<Style*>* styles = Style::findAll()->toVector();
        sort(styles->begin(), styles->end(), reIdLessThanKey());
    }
}