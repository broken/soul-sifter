//
//  Album.h
//  soul-sifter
//
//  Created by Robby Neale on 12/9/12.
//
//

#ifndef __soul_sifter__Album__
#define __soul_sifter__Album__

#include <string>

using namespace std;

class Album {
public:
    Album();
    ~Album();
    void clear();
    
    static Album* findById(const int id);
    static Album* findByName(const string& name);
    static Album* findByCoverFilepath(const string& filepath);
    
    bool update();
    int save();
    
    const int getId() const;
    void setId(const int id);
    const string& getName() const;
    void setName(const string& name);
    const string& getCoverFilepath() const;
    void setCoverFilepath(const string& coverFilepath);
    const bool getMixed() const;
    void setMixed(const bool mixed);
private:
    int id;
    string name;
    string coverFilepath;
    bool mixed;
};

#endif /* defined(__soul_sifter__Album__) */
