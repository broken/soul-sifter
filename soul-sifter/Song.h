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

#include "BasicGenre.h"
#include "RESong.h"
#include "Style.h"

using namespace std;

class Song {
public:
    Song();
    explicit Song(RESong* song);
    ~Song();
    void clear();
    
    static Song* findById(const int id);
    static Song* findByRESongId(const int id);
    
    bool update();
    const Song* save();
    
    const int getId() const;
    void setId(const int id);
    const string& getArtist() const;
    void setArtist(const string& artist);
    const string& getAlbum() const;
    void setAlbum(const string& album);
    const string& getTrack() const;
    void setTrack(const string& track);
    const string& getTitle() const;
    void setTitle(const string& title);
    const string& getRemix() const;
    void setRemix(const string& remix);
    const string& getFeaturing() const;
    void setFeaturing(const string& featuring);
    const string& getLabel() const;
    void setLabel(const string& label);
    const string& getCatalogId() const;
    void setCatalogId(const string& catalogId);
    const int getReleaseDateYear() const;
    void setReleaseDateYear(const int releaseDateYear);
    const int getReleaseDateMonth() const;
    void setReleaseDateMonth(const int releaseDateMonth);
    const int setReleaseDateDay() const;
    void setReleaseDateDay(const int releaseDateDay);
    const string& getFilepath() const;
    void setFilepath(const string& filepath);
    const int getBasicGenreId() const;
    void setBasicGenreId(const int basicGenreId);
    const BasicGenre* getBasicGenre() const;
    void setBasicGenre(const BasicGenre* basicGenre);
    const int getRESongId() const;
    void setRESongId(const int reSongId);
    const RESong* getRESong() const;
    void setRESong(RESong* reSong);
    const vector<const Style*> getStyles() const;
    void setStyles(vector<const Style*> styles);
    void addToStyle(const Style* style);
    void removeFromStyle(const Style* style);
    
private:
    int id;
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
    int basicGenreId;
    const BasicGenre *basicGenre;
    int reSongId;
    RESong *reSong;
    vector<const Style*> styles;
};

#endif /* defined(__soul_sifter__Song__) */
