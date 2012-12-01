//
//  RapidEvolutionDatabaseStylesHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseStylesHandler__
#define __soul_sifter__RapidEvolutionDatabaseStylesHandler__

#include "DTAbstractHandler.h"

class RapidEvolutionDatabaseStylesHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseStylesHandler(xercesc::SAX2XMLReader* parser,
                                        DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseStylesHandler__) */
