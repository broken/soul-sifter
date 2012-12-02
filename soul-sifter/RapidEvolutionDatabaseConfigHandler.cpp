//
//  RapidEvolutionDatabaseConfigHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseConfigHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"
#include "RapidEvolutionDatabaseConfigSettingsHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseConfigHandler::RapidEvolutionDatabaseConfigHandler(SAX2XMLReader* parser,
                                                                         DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("config")) {
    childHandlers = new DTAbstractHandler*[2];
    childHandlers[0] = new RapidEvolutionDatabaseConfigSettingsHandler(parser, this);
    childHandlers[1] = NULL;
}
