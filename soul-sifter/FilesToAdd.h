//
//  FilesToAdd.h
//  soul-sifter
//
//  Created by Robby Neale on 8/10/13.
//
//

#ifndef __soul_sifter__FilesToAdd__
#define __soul_sifter__FilesToAdd__

#include <string>
#include <queue>

#include "Song.h"

using namespace std;

namespace dogatech {
  namespace soulsifter {
  
    class FilesToAdd {
    public:
      FilesToAdd();
      ~FilesToAdd();
    
      void addFile(string path);
      void addSong(Song *song);
      
      bool pullSong(Song** song);
      bool pullFile(string** path);
      
      const string* coverPath() const;
      void switchCover();
    
    private:
      queue<Song*> songs;
      vector<string*> images;
      queue<string*> misc;
      int coverIndex;
    };
  
  }  // namespace soulsifter
}  // namespace dogatech

#endif /* defined(__soul_sifter__FilesToAdd__) */
