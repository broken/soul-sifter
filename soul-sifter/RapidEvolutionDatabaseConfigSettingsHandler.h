//
//  RapidEvolutionDatabaseConfigSettingsHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseConfigSettingsHandler__
#define __soul_sifter__RapidEvolutionDatabaseConfigSettingsHandler__

#include "DTAbstractHandler.h"
#include "RESetting.h"

namespace soulsifter {

class RapidEvolutionDatabaseConfigSettingsHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseConfigSettingsHandler(xercesc::SAX2XMLReader* parser,
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
    
    void characters(const XMLCh* const chars, const XMLSize_t length);
private:
    const XMLCh* const qname;
    RESetting reSetting;
};
    
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseConfigSettingsHandler__) */
