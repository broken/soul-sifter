//
//  RapidEvolutionDatabaseConfigUserHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigUserHandler.h"

#include <xercesc/util/XMLString.hpp>

#include "REXML.h"

using namespace xercesc;

RapidEvolutionDatabaseConfigUserHandler::RapidEvolutionDatabaseConfigUserHandler(SAX2XMLReader* parser,
                                                                                 DTAbstractHandler* parentHandler) :
DTCopyHandler::DTCopyHandler(parser, parentHandler),
qname(XMLString::transcode("user")) {
}

void RapidEvolutionDatabaseConfigUserHandler::init() {
    xml = REXML::findByName("user");
    if (!xml) {
        xml = new REXML();
        xml->setName("user");
    }
    text = &xml->getXmlRef();
}

void RapidEvolutionDatabaseConfigUserHandler::commit() {
    if (xml->getId()) {
        xml->update();
    } else {
        REXML* saved = xml->save();
        delete saved;
        delete xml;
    }
}
