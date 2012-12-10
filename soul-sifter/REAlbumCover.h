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

namespace sql {
    class ResultSet;
}

using namespace std;

namespace soulsifter {

class REAlbumCover {
public:
    REAlbumCover();
    ~REAlbumCover();
    
    class REAlbumCoverIterator {
    public:
        explicit REAlbumCoverIterator(sql::ResultSet* resultset);
        ~REAlbumCoverIterator();
        
        bool next(REAlbumCover* albumcover);
    private:
        sql::ResultSet* rs;
        
        REAlbumCoverIterator();
    };
    
    static REAlbumCover* findById(const int id);
    static REAlbumCover* findByREId(const string& reId);
    static REAlbumCoverIterator* findAll();
    
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

}

#endif /* defined(__soul_sifter__REAlbumCover__) */
