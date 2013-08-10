//
//  RapidEvolutionDatabaseStylesHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseStylesHandler__
#define __soul_sifter__RapidEvolutionDatabaseStylesHandler__

#include <vector>

#include "DTAbstractHandler.h"

using namespace std;

namespace dogatech {
namespace soulsifter {
    
class Style;

class RapidEvolutionDatabaseStylesHandler : public DTAbstractHandler {
public:
    RapidEvolutionDatabaseStylesHandler(xercesc::SAX2XMLReader* parser,
                                        DTAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
    
    void endElement(const XMLCh* const uri,
                    const XMLCh* const localName,
                    const XMLCh* const qName);
    
private:
    const XMLCh* const qname;
    
    vector<pair<int, int> > childStyles;  // re_id -> child re_id
};
    
}
}

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseStylesHandler__) */
