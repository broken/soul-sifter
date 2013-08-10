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
#include "RapidEvolutionDatabaseConfigColumnsHandler.h"
#include "RapidEvolutionDatabaseConfigTablesHandler.h"
#include "RapidEvolutionDatabaseConfigUserHandler.h"

using namespace xercesc;

namespace dogatech {
namespace soulsifter {

RapidEvolutionDatabaseConfigHandler::RapidEvolutionDatabaseConfigHandler(SAX2XMLReader* parser,
                                                                         DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("config")) {
    childHandlers = new DTAbstractHandler*[5];
    childHandlers[0] = new RapidEvolutionDatabaseConfigSettingsHandler(parser, this);
    childHandlers[1] = new RapidEvolutionDatabaseConfigColumnsHandler(parser, this);
    childHandlers[2] = new RapidEvolutionDatabaseConfigTablesHandler(parser, this);
    childHandlers[3] = new RapidEvolutionDatabaseConfigUserHandler(parser, this);
    childHandlers[4] = NULL;
}
    
}
}
