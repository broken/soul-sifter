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

using namespace std;

class Style {
public:
    Style();
    ~Style();
    
    static const Style* findById(const int id);
    static const Style* findByREId(const int reId);
    static bool findStyle(Style* style);  // deprecated
    static void findAll(const vector<const Style*>** stylesPtr);
    
    bool update();
    const Style* save();
    
    void clear();  // deprecated
    
    const int getId() const;
    void setId(const int id);
    const string& getName() const;
    void setName(const string& name);
    const int getREId() const;
    void setREId(const int reId);
    const string& getREName() const;
    void setREName(const string& reName);
    
private:
    // main params
    int id;
    string name;
    // rapid evolution params
    int re_id;
    string re_name;
};

#endif /* defined(__soul_sifter__Style__) */
