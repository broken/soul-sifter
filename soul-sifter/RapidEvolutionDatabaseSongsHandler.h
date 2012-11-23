//
//  RapidEvolutionDatabaseSongsHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseSongsHandler__
#define __soul_sifter__RapidEvolutionDatabaseSongsHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class RapidEvolutionDatabaseSongsHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseSongsHandler(xercesc::SAX2XMLReader* parser,
                                       RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseSongsHandler__) */