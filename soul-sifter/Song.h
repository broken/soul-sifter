//
//  Song.h
//  soul-sifter
//
//  Created by Robby Neale on 11/27/12.
//
//

#ifndef __soul_sifter__Song__
#define __soul_sifter__Song__

#include <string>
#include <vector>

#include "BasicGenre.h"
#include "ReSong.h"
#include "Style.h"

using namespace std;

class Song {
public:
    Song();
    ~Song();
    
private:
    string artist;
    string album;
    string track;
    string title;
    string remix;
    string featuring;
    string label;
    string catalogId;
    int releaseDateYear;
    int releaseDateMonth;
    int releaseDateDay;
    string filepath;
    BasicGenre *basicGenre;
    ReSong *reSong;
    vector<Style> styles;
};

#endif /* defined(__soul_sifter__Song__) */
