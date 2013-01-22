//
//  Style.h
//  soul-sifter
//
//  Created by Robby Neale on 11/9/12.
//
//

#ifndef __soul_sifter__Style__
#define __soul_sifter__Style__

#include <string>
#include <vector>

namespace sql {
    class ResultSet;
}

using namespace std;

namespace soulsifter {
    
    class Style {
    public:
        Style();
        ~Style();
        void clear();
        
        bool operator<(const Style& style) const;
        bool operator>(const Style& style) const;
        
        static const Style* findById(const int id);
        static Style* findByREId(const int reId);
        static void findAll(const vector<Style*>** stylesPtr);
        static void findAllSorted(const vector<Style*>** stylesPtr);
        
        bool update();
        int save();
        int addChild(Style* child);
        
        const int getId() const;
        void setId(const int id);
        const string& getName() const;
        void setName(const string& name);
        const int getREId() const;
        void setREId(const int reId);
        const string& getREName() const;
        void setREName(const string& reName);
        
        void getChildren(const vector<Style*>** stylesPtr) const;
        void getParents(const vector<Style*>** stylesPtr) const;
        
    private:
        // main params
        int id;
        string name;
        // rapid evolution params
        int re_id;
        string re_name;
        
        vector<Style*> children;
        vector<Style*> parents;
        
        static vector<Style*>* getStaticStyles();
        static Style* findByIdMutable(const int id);
        
        static void populateFields(const sql::ResultSet* rs, Style* style);
    };
    
}

#endif /* defined(__soul_sifter__Style__) */
