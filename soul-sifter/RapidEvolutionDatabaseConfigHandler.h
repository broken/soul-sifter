//
//  RapidEvolutionDatabaseConfigHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseConfigHandler__
#define __soul_sifter__RapidEvolutionDatabaseConfigHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class RapidEvolutionDatabaseConfigHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseConfigHandler(xercesc::SAX2XMLReader* parser,
                                        RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseConfigHandler__) */
