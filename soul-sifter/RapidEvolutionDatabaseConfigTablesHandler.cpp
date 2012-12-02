//
//  RapidEvolutionDatabaseConfigTablesHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigTablesHandler.h"

#include <xercesc/util/XMLString.hpp>

#include "REXML.h"

using namespace xercesc;

RapidEvolutionDatabaseConfigTablesHandler::RapidEvolutionDatabaseConfigTablesHandler(SAX2XMLReader* parser,
                                                                                     DTAbstractHandler* parentHandler) :
DTCopyHandler::DTCopyHandler(parser, parentHandler),
qname(XMLString::transcode("tables")) {
}

void RapidEvolutionDatabaseConfigTablesHandler::init() {
    xml = REXML::findByName("tables");
    if (!xml) {
        xml = new REXML();
        xml->setName("tables");
    }
    text = &xml->getXmlRef();
}

void RapidEvolutionDatabaseConfigTablesHandler::commit() {
    if (xml->getId()) {
        xml->update();
    } else {
        REXML* saved = xml->save();
        delete saved;
        delete xml;
    }
}
