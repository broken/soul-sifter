//
//  MusicManager.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#include <hash_map.h>
#include <string>

using namespace std;

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
    
    // paths
    string getCopyToPath();
    bool moveSong(Song* song);
    void moveImage(const string filepath);
    void populateStagingDirectory();
    void flushStagingDirectory();
    
    // db updates
    void updateDatabaseBasicGenres();

private:
    // tags
    Song *lastParsedSong;
    Song *lastSongFixed;
    
    // paths
    hash_map<string, BasicGenre*> artistToGenre;
    
    // singleton
    MusicManager();
    MusicManager(MusicManager const&);
    void operator=(MusicManager const&);
    
    void initializePathMembers();
};
    
}
