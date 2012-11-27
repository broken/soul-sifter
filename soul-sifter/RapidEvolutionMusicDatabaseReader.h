//
//  RapidEvolutionMusicDatabaseReader.h
//  soul-sifter
//
//  Created by Robby Neale on 11/4/12.
//
//

#ifndef __soul_sifter__RapidEvolutionMusicDatabaseReader__
#define __soul_sifter__RapidEvolutionMusicDatabaseReader__

#include "RapidEvolutionDatabaseHandler.h"

class RapidEvolutionMusicDatabaseReader {
public:
    RapidEvolutionMusicDatabaseReader();
    
    bool read();
    unsigned long getSrcOffset() {
        return processing ? reDbHandler->getStartTagCount() : 0;
    }
    bool isProcessing();
    unsigned long getSrcLength() {
        return length;
    }
    
private:
    bool processing;
    unsigned long length;
    RapidEvolutionDatabaseHandler* reDbHandler;
    
    void computeMusicDatabaseLength();
};

#endif /* defined(__soul_sifter__RapidEvolutionMusicDatabaseReader__) */