//
//  REAlbumCover.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__REAlbumCover__
#define __soul_sifter__REAlbumCover__

#include <string>

using namespace std;

class REAlbumCover {
public:
    REAlbumCover();
    ~REAlbumCover();
    
    static REAlbumCover* findById(const int id);
    static REAlbumCover* findByREId(const string& reId);
    
    int update();
    int save();
    void clear();
    
    const int getId() const;
    void setId(const int id);
    const string& getREId() const;
    void setREId(const string& id);
    const string& getThumbnail() const;
    void setThumbnail(const string& thumbnail);
private:
    int id;
    string reId;
    string thumbnail;
};

#endif /* defined(__soul_sifter__REAlbumCover__) */
