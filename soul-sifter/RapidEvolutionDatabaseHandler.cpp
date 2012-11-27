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
#include "RapidEvolutionDatabaseAlbumcoversHandler.h"
#include "RapidEvolutionDatabaseArtistsHandler.h"
#include "RapidEvolutionDatabaseConfigHandler.h"
#include "RapidEvolutionDatabaseExcludesHandler.h"
#include "RapidEvolutionDatabaseMixoutsHandler.h"
#include "RapidEvolutionDatabaseSongsHandler.h"
#include "RapidEvolutionDatabaseStylesHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseHandler::RapidEvolutionDatabaseHandler(SAX2XMLReader* parser,
                                                             RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("music_database")) {
    startTagCount = 0;
    childHandlers = new RapidEvolutionDatabaseAbstractHandler*[8];
    childHandlers[0] = new RapidEvolutionDatabaseConfigHandler(parser, this);
    childHandlers[1] = new RapidEvolutionDatabaseStylesHandler(parser, this);
    childHandlers[2] = new RapidEvolutionDatabaseSongsHandler(parser, this);
    childHandlers[3] = new RapidEvolutionDatabaseMixoutsHandler(parser, this);
    childHandlers[4] = new RapidEvolutionDatabaseExcludesHandler(parser, this);
    childHandlers[5] = new RapidEvolutionDatabaseArtistsHandler(parser, this);
    childHandlers[6] = new RapidEvolutionDatabaseAlbumcoversHandler(parser, this);
    childHandlers[7] = NULL;
}

