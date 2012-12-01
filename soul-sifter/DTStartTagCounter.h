//
//  DTStartTagCounter.h
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#ifndef __soul_sifter__DTStartTagCounter__
#define __soul_sifter__DTStartTagCounter__

#include "DTAbstractHandler.h"

class DTStartTagCounter : public DTAbstractHandler {
public:
    DTStartTagCounter(xercesc::SAX2XMLReader* parser,
                      DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return NULL;
    }
};

#endif /* defined(__soul_sifter__DTStartTagCounter__) */
