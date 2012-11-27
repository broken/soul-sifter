//
//  XMLStartTagCounter.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#include "XMLStartTagCounter.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"

using namespace xercesc;

XMLStartTagCounter::XMLStartTagCounter(SAX2XMLReader* parser,
                                       RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler) {
    startTagCount = 0;
}

