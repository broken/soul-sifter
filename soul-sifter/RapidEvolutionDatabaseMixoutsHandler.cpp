//
//  RapidEvolutionDatabaseMixoutsHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseMixoutsHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"
#include "RapidEvolutionDatabaseMixoutsMixoutHandler.h"

using namespace xercesc;

namespace soulsifter {

RapidEvolutionDatabaseMixoutsHandler::RapidEvolutionDatabaseMixoutsHandler(SAX2XMLReader* parser,
                                                                           DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("mixouts")) {
    childHandlers = new DTAbstractHandler*[2];
    childHandlers[0] = new RapidEvolutionDatabaseMixoutsMixoutHandler(parser, this);
    childHandlers[1] = NULL;
}
    
}
