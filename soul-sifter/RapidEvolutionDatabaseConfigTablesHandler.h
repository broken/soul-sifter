//
//  RapidEvolutionDatabaseConfigTablesHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseConfigTablesHandler__
#define __soul_sifter__RapidEvolutionDatabaseConfigTablesHandler__

#include "DTCopyHandler.h"
#include "REXml.h"

namespace soulsifter {

class RapidEvolutionDatabaseConfigTablesHandler : public DTCopyHandler {
public:
    RapidEvolutionDatabaseConfigTablesHandler(xercesc::SAX2XMLReader* parser,
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

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseConfigTablesHandler__) */
