//
//  RapidEvolutionDatabaseConfigColumnsHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseConfigColumnsHandler__
#define __soul_sifter__RapidEvolutionDatabaseConfigColumnsHandler__

#include "DTCopyHandler.h"
#include "REXML.h"

namespace soulsifter {

class RapidEvolutionDatabaseConfigColumnsHandler : public DTCopyHandler {
public:
    RapidEvolutionDatabaseConfigColumnsHandler(xercesc::SAX2XMLReader* parser,
                                               DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
    
    void init();
    void commit();
    
private:
    const XMLCh* const qname;
    REXml xml;
};
    
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseConfigColumnsHandler__) */
