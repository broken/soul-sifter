//
//  Track.h
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#ifndef __soul_sifter__Track__
#define __soul_sifter__Track__

#include <iostream>
#include <string>

using namespace std;

namespace soulsifter {
    
    class Track {
        int id;
        int re_id;
        string artist;
        string album;
        string trackNum;
        string title;
        string remix;
        string featuring;
        string label;
        string catalogId;
        string releaseDateYear;
        string releaseDateMonth;
        string releaseDateDay;
        
        string basicGenre;
        string* genres;
        string filePath;
        
        Track();
        ~Track();
        
        static void getTrack(Track* track);
    };
    
}

#endif /* defined(__soul_sifter__Track__) */
