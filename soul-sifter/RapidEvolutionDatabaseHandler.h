//
//  RapidEvolutionDatabaseHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/4/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseHandler__
#define __soul_sifter__RapidEvolutionDatabaseHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class RapidEvolutionDatabaseHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseHandler(xercesc::SAX2XMLReader* parser,
                                  RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};


#endif /* defined(__soul_sifter__RapidEvolutionDatabaseHandler__) */
