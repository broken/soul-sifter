//
//  RapidEvolutionDatabaseSongsSongHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseSongsSongHandler.h"

#include <iostream>

#include <xercesc/sax2/DefaultHandler.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"

using namespace std;
using namespace xercesc;

RapidEvolutionDatabaseSongsSongHandler::RapidEvolutionDatabaseSongsSongHandler(SAX2XMLReader* parser,
                                                                               RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("song")) {
}

void RapidEvolutionDatabaseSongsSongHandler::startElement(const   XMLCh* const    uri,
                                                          const   XMLCh* const    localname,
                                                          const   XMLCh* const    qname,
                                                          const   Attributes&     attrs) {
    char* message = XMLString::transcode(localname);
    cout << "I saw element: "<< message << endl;
    XMLString::release(&message);
}
