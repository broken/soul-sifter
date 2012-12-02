//
//  RapidEvolutionDatabaseConfigColumnsHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigColumnsHandler.h"

#include <xercesc/util/XMLString.hpp>

#include "REXML.h"

using namespace xercesc;

RapidEvolutionDatabaseConfigColumnsHandler::RapidEvolutionDatabaseConfigColumnsHandler(SAX2XMLReader* parser,
                                                                                       DTAbstractHandler* parentHandler) :
DTCopyHandler::DTCopyHandler(parser, parentHandler),
qname(XMLString::transcode("columns")) {
}

void RapidEvolutionDatabaseConfigColumnsHandler::init() {
    xml = REXML::findByName("columns");
    if (!xml) {
        xml = new REXML();
        xml->setName("columns");
    }
    text = &xml->getXmlRef();
}

void RapidEvolutionDatabaseConfigColumnsHandler::commit() {
    if (xml->getId()) {
        xml->update();
    } else {
        REXML* saved = xml->save();
        delete saved;
        delete xml;
    }
}