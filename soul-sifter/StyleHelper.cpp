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
    
    void Style::findAll(const vector<Style*>** stylesPtr) {
        vector<Style*>* styles = getStaticStyles();
        (*stylesPtr) = styles;
    }
    
    void Style::findAllSorted(const vector<Style*>** stylesPtr) {
        vector<Style*>* styles = getStaticStyles();
        sort(styles->begin(), styles->end(), lessThanKey());
        (*stylesPtr) = styles;
    }
    
# pragma mark persistence
    
    int Style::addChild(Style* child) {
        try {
            for (vector<Style*>::const_iterator it = children.begin(); it != children.end(); ++it) {
                if ((*it)->getId() == child->getId()) {
                    return 0;
                }
            }
            children.push_back(child);
            child->parents.push_back(this);
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into StyleChildren (parentId, childId) values (?, ?)");
            ps->setInt(1, id);
            ps->setInt(2, child->getId());
            return ps->executeUpdate();
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            return NULL;
        }
    }
}