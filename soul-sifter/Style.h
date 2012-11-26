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

using namespace std;

class Style {
public:
    // main params
    int id;
    string name;
    // rapid evolution params
    int re_id;
    string re_name;
    
    Style();
    ~Style();
    
    static bool findStyle(Style* style);
    
    bool update();
    bool save();
    
    void clear();
};

#endif /* defined(__soul_sifter__Style__) */
