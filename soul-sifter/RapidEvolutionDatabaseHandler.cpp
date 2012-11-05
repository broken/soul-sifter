//
//  RapidEvolutionDatabaseHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/4/12.
//
//

#include "RapidEvolutionDatabaseHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"
#include "RapidEvolutionDatabaseSongsHandler.h"
#include "RapidEvolutionDatabaseStylesHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseHandler::RapidEvolutionDatabaseHandler(SAX2XMLReader* parser,
                                                             RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("music_database")) {
    childHandlers = new RapidEvolutionDatabaseAbstractHandler*[3];
    childHandlers[0] = new RapidEvolutionDatabaseSongsHandler(parser, this);
    childHandlers[1] = new RapidEvolutionDatabaseStylesHandler(parser, this);
    childHandlers[2] = NULL;
}

