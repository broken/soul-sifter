//
//  FilesToAdd.cpp
//  soul-sifter
//
//  Created by Robby Neale on 8/10/13.
//
//  Class to help manage what files to add to the library.

#include "FilesToAdd.h"

#include <iostream>

#include <boost/algorithm/string/predicate.hpp>

#include "MusicManager.h"
#include "QueueUtil.h"
#include "DTVectorUtil.h"

namespace dogatech {
  namespace soulsifter {
  
    FilesToAdd::FilesToAdd()
    : coverIndex(0) {
    }
  
    FilesToAdd::~FilesToAdd() {
      deleteQueuePointers(&songs);
      deleteVectorPointers(&images);
      deleteQueuePointers(&misc);
    }
    
    void FilesToAdd::clear() {
      coverIndex = 0;
      cover = NULL;
      deleteQueuePointers(&songs);
      deleteVectorPointers(&images);
      deleteQueuePointers(&misc);
    }
  
    // TODO test if it's a directory and loop over it and process zips & rars
    void FilesToAdd::addFile(string path) {
    
      // music files
      // TODO support more than just mp3
      if (boost::algorithm::iends_with(path, ".mp3")) {
        Song *song = new Song();
        song->setFilepath(path);
        MusicManager::getInstance().readTagsFromSong(song);
        songs.push(song);
        return;
      }
    
      // images
      if (boost::algorithm::iends_with(path, ".jpg") ||
          boost::algorithm::iends_with(path, ".jpeg") ||
          boost::algorithm::iends_with(path, ".gif") ||
          boost::algorithm::iends_with(path, ".png")) {
        string* image = new string(path);
        images.push_back(image);
        cover = images.at(coverIndex);
        return;
      }
    
      // misc files
      if (!boost::algorithm::iends_with(path, ".nfo") &&
          !boost::algorithm::iends_with(path, ".txt") &&
          !boost::algorithm::iends_with(path, ".sfv") &&
          !boost::algorithm::iends_with(path, ".m3u")) {
        cout << "Unknown file type to be copied: " << path << endl;
      }
      string* file = new string(path);
      misc.push(file);
    }
    
    void FilesToAdd::addSong(Song *song) {
      songs.push(song);
      
      if (song->getAlbum() != NULL && song->getAlbum()->getCoverFilepath().length() > 0) {
        images.push_back(new string(song->getAlbum()->getCoverFilepath()));
      }
    }
    
    bool FilesToAdd::pullSong(Song** song) {
      if (songs.empty()) return false;
      *song = songs.front();
      songs.pop();
      return true;
    }
    
    bool FilesToAdd::pullFile(string** path) {
      if (images.empty() && misc.empty()) return false;
      if (!images.empty()) {
        *path = images.back();
        images.pop_back();
      } else {
        *path = misc.front();
        misc.pop();
      }
      return true;
    }
  
    const string* FilesToAdd::coverPath() const {
        return cover != NULL ? cover : images.empty() ? NULL : images.at(coverIndex);
    }
    
    void FilesToAdd::switchCover() {
      ++coverIndex;
      if (images.empty() || coverIndex >= images.size()) {
        coverIndex = 0;
      }
      cover = images.at(coverIndex);
    }
    
  }  // namespace soulsifter
}  // namespace dogatech
