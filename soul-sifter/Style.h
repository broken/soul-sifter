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

struct Style {
    int id;
    std::string name;
    int re_id;
    std::string re_name;
    
    Style() :
    id(0),
    name(""),
    re_id(0),
    re_name("") {
    }
};

#endif /* defined(__soul_sifter__Style__) */
