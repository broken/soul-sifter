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

#include <cppconn/resultset.h>

#include "Album.h"
#include "RESong.h"
#include "Style.h"

using namespace std;

namespace soulsifter {

class Song {
public:
    Song();
    explicit Song(const Song& song);
    explicit Song(RESong* song);
    ~Song();
    void clear();
    
    static Song* findById(const int id);
    static Song* findByRESongId(const int id);
    static void findSongsByStyle(const Style& style, vector<Song*>** songsPtr);
    
    bool update();
    const Song* save();
    
    const int getId() const;
    void setId(const int id);
    const string& getArtist() const;
    void setArtist(const string& artist);
    const string& getTrack() const;
    void setTrack(const string& track);
    const string& getTitle() const;
    void setTitle(const string& title);
    const string& getRemix() const;
    void setRemix(const string& remix);
    const string& getFeaturing() const;
    void setFeaturing(const string& featuring);
    const string& getFilepath() const;
    void setFilepath(const string& filepath);
    const int getRESongId() const;
    void setRESongId(const int reSongId);
    const RESong* getRESong() const;
    void setRESong(RESong* reSong);
    const vector<const Style*> getStyles() const;
    void setStyles(vector<const Style*> styles);
    void addToStyle(const Style* style);
    void removeFromStyle(const Style* style);
    const int getRating() const;
    void setRating(const int rating);
    const int getAlbumId() const;
    void setAlbumId(const int albumId);
    Album* getAlbum() const;
    void setAlbum(Album* album);
    
private:
    int id;
    string artist;
    string track;
    string title;
    string remix;
    string featuring;
    string filepath;
    int reSongId;
    RESong *reSong;
    vector<const Style*> styles;
    int rating;
    int albumId;
    Album *album;
};
    
}

#endif /* defined(__soul_sifter__Song__) */
