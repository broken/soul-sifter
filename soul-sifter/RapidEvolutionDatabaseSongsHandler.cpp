//
//  RapidEvolutionDatabaseSongsHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseSongsHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"
#include "RapidEvolutionDatabaseSongsSongHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseSongsHandler::RapidEvolutionDatabaseSongsHandler(SAX2XMLReader* parser,
                                                                       RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("songs")) {
    childHandlers = new RapidEvolutionDatabaseAbstractHandler*[2];
    childHandlers[0] = new RapidEvolutionDatabaseSongsSongHandler(parser, this);
    childHandlers[1] = NULL;
}
