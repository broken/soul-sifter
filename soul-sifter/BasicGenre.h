//
//  BasicGenre.h
//  soul-sifter
//
//  Created by Robby Neale on 11/27/12.
//
//

#ifndef __soul_sifter__BasicGenre__
#define __soul_sifter__BasicGenre__

#include <string>
#include <vector>

using namespace std;

namespace soulsifter {

class BasicGenre {
public:
    BasicGenre();
    ~BasicGenre();
    
    static const BasicGenre* findById(const int id);
    static const BasicGenre* findByName(const string& name);
    static const BasicGenre* findByFilepath(const string& filepath);
    static void findAll(const vector<const BasicGenre*>** genresPtr);
    
    bool update();
    int save();
    
    const int getId() const;
    void setId(const int id);
    const string& getName() const;
    void setName(const string& name);
private:
    int id;
    string name;
};
    
}

#endif /* defined(__soul_sifter__BasicGenre__) */
