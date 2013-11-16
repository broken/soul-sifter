//
//  AudioAnalyzer.h
//  soul-sifter
//
//  Created by Robby Neale on 11/15/13.
//
//

#ifndef soul_sifter_AudioAnalyzer_h
#define soul_sifter_AudioAnalyzer_h


namespace dogatech {
  namespace soulsifter {
    
    class Song;
    
    class AudioAnalyzer {
    public:
      static void analyzeKey(Song* song);
    };
    
  }
}

#endif
