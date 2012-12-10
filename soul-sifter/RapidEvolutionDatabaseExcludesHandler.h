//
//  RapidEvolutionDatabaseExcludesHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseExcludesHandler__
#define __soul_sifter__RapidEvolutionDatabaseExcludesHandler__

#include "DTAbstractHandler.h"

namespace soulsifter {

class RapidEvolutionDatabaseExcludesHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseExcludesHandler(xercesc::SAX2XMLReader* parser,
                                          DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};
    
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseExcludesHandler__) */
