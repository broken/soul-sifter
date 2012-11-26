//
//  RapidEvolutionDatabaseStylesHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseStylesHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"
#include "RapidEvolutionDatabaseStylesStyleHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseStylesHandler::RapidEvolutionDatabaseStylesHandler(SAX2XMLReader* parser,
                                                                         RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("styles")) {
    childHandlers = new RapidEvolutionDatabaseAbstractHandler*[2];
    childHandlers[0] = new RapidEvolutionDatabaseStylesStyleHandler(parser, this);
    childHandlers[1] = NULL;
}
