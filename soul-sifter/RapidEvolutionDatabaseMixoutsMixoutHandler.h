//
//  RapidEvolutionDatabaseMixoutsMixoutHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 12/3/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseMixoutsMixoutHandler__
#define __soul_sifter__RapidEvolutionDatabaseMixoutsMixoutHandler__

#include "DTAbstractHandler.h"

#include <string>

#include <boost/any.hpp>

#include "Mix.h"

namespace soulsifter {

class RapidEvolutionDatabaseMixoutsMixoutHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseMixoutsMixoutHandler(xercesc::SAX2XMLReader* parser,
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
    Mix mix;
    
    boost::any fieldPointer;
    string addonStr;
    
    // attributes
    const XMLCh* const from_unique_id_elem;
    const XMLCh* const to_unique_id_elem;
    const XMLCh* const bpm_diff_elem;
    const XMLCh* const rank_elem;
    const XMLCh* const comments_elem;
    const XMLCh* const addon_elem;
};
    
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseMixoutsMixoutHandler__) */
