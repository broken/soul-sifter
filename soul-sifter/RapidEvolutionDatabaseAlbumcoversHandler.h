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

#include "REAlbumCover.h"

class RapidEvolutionDatabaseAlbumcoversHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseAlbumcoversHandler(xercesc::SAX2XMLReader* parser,
                                             DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
    
    void startElement(const XMLCh* const uri,
                      const XMLCh* const localname,
                      const XMLCh* const qname,
                      const xercesc::Attributes& attrs);
    
    void endElement(const XMLCh* const uri,
                    const XMLCh* const localName,
                    const XMLCh* const qName);
private:
    const XMLCh* const qname;
    const XMLCh* const acQname;
    REAlbumCover* albumcover;
    
    // attributes
    const XMLCh* const id_attrib;
    const XMLCh* const thumbnail_attrib;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseAlbumcoversHandler__) */
