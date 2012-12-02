//
//  RapidEvolutionDatabaseConfigUserHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseConfigUserHandler__
#define __soul_sifter__RapidEvolutionDatabaseConfigUserHandler__

#include "DTCopyHandler.h"

class REXML;

class RapidEvolutionDatabaseConfigUserHandler : public DTCopyHandler {
public:
    RapidEvolutionDatabaseConfigUserHandler(xercesc::SAX2XMLReader* parser,
                                            DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
    
    void init();
    void commit();
    
private:
    const XMLCh* const qname;
    REXML* xml;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseConfigUserHandler__) */
