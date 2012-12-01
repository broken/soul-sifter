//
//  RapidEvolutionDatabaseAlbumcoversHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseAlbumcoversHandler__
#define __soul_sifter__RapidEvolutionDatabaseAlbumcoversHandler__

#include "DTAbstractHandler.h"

class RapidEvolutionDatabaseAlbumcoversHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseAlbumcoversHandler(xercesc::SAX2XMLReader* parser,
                                             DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseAlbumcoversHandler__) */
