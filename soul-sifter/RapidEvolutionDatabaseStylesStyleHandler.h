//
//  RapidEvolutionDatabaseStylesStyleHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseStylesStyleHandler__
#define __soul_sifter__RapidEvolutionDatabaseStylesStyleHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

class RapidEvolutionDatabaseStylesStyleHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseStylesStyleHandler(xercesc::SAX2XMLReader* parser,
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
    
    // attributes
    const XMLCh* const category_only_attrib;
    const XMLCh* const child_ids_attrib;
    const XMLCh* const description_attrib;
    const XMLCh* const id_attrib;
    const XMLCh* const name_attrib;
    const XMLCh* const parent_ids_attrib;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseStylesStyleHandler__) */
