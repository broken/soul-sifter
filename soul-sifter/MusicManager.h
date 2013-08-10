//
//  MusicManager.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#ifndef __soul_sifter__MusicManager__
#define __soul_sifter__MusicManager__

#include <string>

#include <boost/unordered_map.hpp>

using namespace std;

namespace dogatech {
namespace soulsifter {

class BasicGenre;
class Song;

class MusicManager {
public:
    ~MusicManager();
    static MusicManager& getInstance() {
        static MusicManager instance;  // guaranteed to be destroyed
        // instantiated on first use
        return instance;
    }
    
    // tags
    void readTagsFromSong(Song* song);
    void writeTagsToSong(Song* song);  // takes ownership of song here
    
    // monitor changes
    Song* updateSongWithChanges(const Song& song);
    void setNewSongChanges(const Song& song);
    void updateLastSongAlbumArtWithImage(const string& filepath);
    
    // paths
    string getCopyToPath();
    bool moveSong(Song* song);
    bool moveImage(const string& filepath);
    void populateStagingDirectory();
    void flushStagingDirectory();
    
    // db updates
    void updateDatabaseBasicGenres();
    const BasicGenre* findBasicGenreForArtist(const string& artist);

private:
    // tags
    Song *lastParsedSong;
    Song *lastSongFixed;
    
    // paths
    boost::unordered_map<string, const BasicGenre*> artistToGenre;
    string imgDestinationPath;
    
    // singleton
    MusicManager();
    MusicManager(MusicManager const&);
    void operator=(MusicManager const&);
    
    void initializePathMembers();
};
    
}
}

#endif /* defined(__soul_sifter__MusicManager__) */
