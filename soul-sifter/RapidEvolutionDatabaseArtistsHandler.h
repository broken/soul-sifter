//
//  RapidEvolutionDatabaseArtistsHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseArtistsHandler__
#define __soul_sifter__RapidEvolutionDatabaseArtistsHandler__

#include "DTAbstractHandler.h"

namespace dogatech {
namespace soulsifter {

class RapidEvolutionDatabaseArtistsHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseArtistsHandler(xercesc::SAX2XMLReader* parser,
                                         DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
private:
    const XMLCh* const qname;
};
    
}
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseArtistsHandler__) */
