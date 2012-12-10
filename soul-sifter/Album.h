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

#include "BasicGenre.h"

using namespace std;

namespace soulsifter {

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
    
    const string reReleaseDate() const;
    
    const int getId() const;
    void setId(const int id);
    const string& getName() const;
    void setName(const string& name);
    const string& getCoverFilepath() const;
    void setCoverFilepath(const string& coverFilepath);
    const bool getMixed() const;
    void setMixed(const bool mixed);
    const string& getLabel() const;
    void setLabel(const string& label);
    const string& getCatalogId() const;
    void setCatalogId(const string& catalogId);
    const int getReleaseDateYear() const;
    void setReleaseDateYear(const int releaseDateYear);
    const int getReleaseDateMonth() const;
    void setReleaseDateMonth(const int releaseDateMonth);
    const int getReleaseDateDay() const;
    void setReleaseDateDay(const int releaseDateDay);
    const int getBasicGenreId() const;
    void setBasicGenreId(const int basicGenreId);
    const BasicGenre* getBasicGenre() const;
    void setBasicGenre(const BasicGenre* basicGenre);
private:
    int id;
    string name;
    string coverFilepath;
    bool mixed;
    string label;
    string catalogId;
    int releaseDateYear;
    int releaseDateMonth;
    int releaseDateDay;
    int basicGenreId;
    const BasicGenre *basicGenre;
};
    
}

#endif /* defined(__soul_sifter__Album__) */
