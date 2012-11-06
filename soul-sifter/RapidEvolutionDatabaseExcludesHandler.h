//
//  RapidEvolutionDatabaseExcludesHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseExcludesHandler__
#define __soul_sifter__RapidEvolutionDatabaseExcludesHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class RapidEvolutionDatabaseExcludesHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseExcludesHandler(xercesc::SAX2XMLReader* parser,
                                          RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseExcludesHandler__) */
