//
//  RapidEvolutionDatabaseMixoutsHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseMixoutsHandler__
#define __soul_sifter__RapidEvolutionDatabaseMixoutsHandler__

#include "DTAbstractHandler.h"

namespace soulsifter {

class RapidEvolutionDatabaseMixoutsHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseMixoutsHandler(xercesc::SAX2XMLReader* parser,
                                         DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};
    
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseMixoutsHandler__) */
