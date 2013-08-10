//
//  RapidEvolutionMusicDatabaseWriter.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__RapidEvolutionMusicDatabaseWriter__
#define __soul_sifter__RapidEvolutionMusicDatabaseWriter__

namespace dogatech {
namespace soulsifter {

class RapidEvolutionMusicDatabaseWriter {
public:
    RapidEvolutionMusicDatabaseWriter();
    
    void write();
    
private:
    bool processing;
};

}
}

#endif /* defined(__soul_sifter__RapidEvolutionMusicDatabaseWriter__) */
