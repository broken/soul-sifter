//
//  ReSong.h
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#ifndef __soul_sifter__ReSong__
#define __soul_sifter__ReSong__

#include <string>

using namespace std;

class ReSong {
public:
    int unique_id;
    string songid_winfo;
    string songid;
    string shortid;
    string shortid_winfo;
    string artist;
    string album;
    string track;
    string title;
    string time;
    string time_signature;
    string filename;
    string digital_only;
    string compilation;
    string key_start;
    int key_accuracy;
    double bpm_start;
    int bpm_accuracy;
    short rating;
    string date_added;
    string catalog_id;  // custom4
    string label;  // custom3
    string remix;
    int num_plays;
    string comments;
    string release_date;  // custom2
    string featuring;  // custom1
    string key_end;
    string disabled;
    double bpm_end;
    int beat_intensity;
    double replay_gain;
    string album_cover;
    string styles_bitmask;
    
    ReSong();
    ~ReSong();
    
    static bool lookup(ReSong *song);
    
    bool update();
    bool save();
    
    void clear();
};

#endif /* defined(__soul_sifter__ReSong__) */
