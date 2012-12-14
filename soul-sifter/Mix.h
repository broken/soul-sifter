//
//  Mixes.h
//  soul-sifter
//
//  Created by Robby Neale on 12/3/12.
//
//

#ifndef __soul_sifter__Mix__
#define __soul_sifter__Mix__

#include <string>
#include <vector>

#include "Song.h"

using namespace std;

namespace soulsifter {
    
class RapidEvolutionDatabaseMixoutsMixoutHandler;

class Mix {
public:
    friend class RapidEvolutionDatabaseMixoutsMixoutHandler;
    
    class MixResultSet {
    public:
        explicit MixResultSet(sql::ResultSet* resultset);
        ~MixResultSet();
        
        bool next(Mix* mix);
    private:
        sql::ResultSet* rs;
        
        MixResultSet();
    };
    
    Mix();
    ~Mix();
    void clear();
    
    static const Mix* findById(const int id);
    static Mix* findBySongIds(const int outSongId, const int inSongId);
    static MixResultSet* findAll();
    
    bool update();
    int save();
    
    const int getId() const;
    void setId(const int id);
    const int getOutSongId() const;
    void setOutSongId(const int id);
    const Song* getOutSong();
    void setOutSong(Song* song);
    const int getInSongId() const;
    void setInSongId(const int id);
    const Song* getInSong();
    void setInSong(Song* song);
    const string& getBPMDiff() const;
    void setBPMDiff(const string& bpmDiff);
    const int getRank() const;
    void setRank(const int rank);
    const string& getComments() const;
    void setComments(const string& comments);
    const bool getAddon() const;
    void setAddon(const bool addon);
    
private:
    int id;
    int outSongId;
    Song *outSong;
    int inSongId;
    Song *inSong;
    string bpmDiff;
    int rank;
    string comments;
    bool addon;
};
    
}

#endif /* defined(__soul_sifter__Mix__) */
