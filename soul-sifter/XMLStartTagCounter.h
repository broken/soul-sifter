//
//  XMLStartTagCounter.h
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#ifndef __soul_sifter__XMLStartTagCounter__
#define __soul_sifter__XMLStartTagCounter__

#include "DTAbstractHandler.h"

class XMLStartTagCounter : public DTAbstractHandler {
public:
    XMLStartTagCounter(xercesc::SAX2XMLReader* parser,
                       DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return NULL;
    }
};

#endif /* defined(__soul_sifter__XMLStartTagCounter__) */
