//
//  XMLStartTagCounter.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#include "XMLStartTagCounter.h"

#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"

using namespace xercesc;

XMLStartTagCounter::XMLStartTagCounter(SAX2XMLReader* parser,
                                       DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler) {
    startTagCount = 0;
}

