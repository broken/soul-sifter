//
//  Style.h
//  soul-sifter
//
//  Created by Robby Neale on 11/9/12.
//
//

#ifndef __soul_sifter__Style__
#define __soul_sifter__Style__

struct Style {
    int db_id;
    int re_id;
    char* name;
    int index;
    
    Style() :
    name(0) {
    }
};

#endif /* defined(__soul_sifter__Style__) */
