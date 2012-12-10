//
//  RapidEvolutionDatabaseSongsHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseSongsHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"
#include "RapidEvolutionDatabaseSongsSongHandler.h"

using namespace xercesc;

namespace soulsifter {

RapidEvolutionDatabaseSongsHandler::RapidEvolutionDatabaseSongsHandler(SAX2XMLReader* parser,
                                                                       DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("songs")) {
    childHandlers = new DTAbstractHandler*[2];
    childHandlers[0] = new RapidEvolutionDatabaseSongsSongHandler(parser, this);
    childHandlers[1] = NULL;
}
    
}
