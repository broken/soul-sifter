//
//  RapidEvolutionDatabaseAlbumcoversHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseAlbumcoversHandler.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseAlbumcoversHandler::RapidEvolutionDatabaseAlbumcoversHandler(SAX2XMLReader* parser,
                                                                                   RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("albumcovers")) {
}
