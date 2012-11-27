//
//  XMLStartTagCounter.h
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#ifndef __soul_sifter__XMLStartTagCounter__
#define __soul_sifter__XMLStartTagCounter__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class XMLStartTagCounter : public RapidEvolutionDatabaseAbstractHandler {
public:
    XMLStartTagCounter(xercesc::SAX2XMLReader* parser,
                       RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return NULL;
    }
};

#endif /* defined(__soul_sifter__XMLStartTagCounter__) */
