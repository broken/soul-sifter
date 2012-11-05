//
//  RapidEvolutionDatabaseSongsSongHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseSongsSongHandler__
#define __soul_sifter__RapidEvolutionDatabaseSongsSongHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class RapidEvolutionDatabaseSongsSongHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseSongsSongHandler(xercesc::SAX2XMLReader* parser,
                                           RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
    
    void startElement(const XMLCh* const uri,
                      const XMLCh* const localname,
                      const XMLCh* const qname,
                      const xercesc::Attributes& attrs);
private:
    const XMLCh* const qname;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseSongsSongHandler__) */
