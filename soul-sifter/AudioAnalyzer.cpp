//
//  AudioAnalyzer.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/9/13.
//
//

#include "AudioAnalyzer.h"

#include <iostream>
#include <stdio.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include "madlld.h"
#include "MiniBpm.h"
#include "Song.h"


namespace dogatech {
  namespace soulsifter {
    
    const Bpms* AudioAnalyzer::analyzeBpm(Song *song) {
      cout << "analyze bpm" << endl;
      
      breakfastquay::MiniBPM miniBpm(44100);
      
      if (boost::algorithm::iends_with(song->getFilepath(), ".mp3")) {
        detectBpm(song->getFilepath().c_str(), boost::bind(&breakfastquay::MiniBPM::process, boost::ref(miniBpm), _1, _2));
      } else {
        cerr << "Unrecognizable file type when analyzing BPM for " << song->getFilepath() << endl;
        return new Bpms;
      }
    
      char buffer[8];
      sprintf(buffer, "%.2f", miniBpm.estimateTempo());
      song->setBpm(buffer);
      
      Bpms *bpm = new Bpms();
      vector<double> candidates = miniBpm.getTempoCandidates();
      int i = 0;
      for (vector<double>::const_iterator it = candidates.begin(); it != candidates.end() && i < 3; ++it, ++i) {
        bpm->candidate[i] = *it;
      }
      
      return bpm;
    }
    
    void AudioAnalyzer::analyzeKey(Song *song) {
      cout << "analyze key" << endl;
    }
    
  }
}