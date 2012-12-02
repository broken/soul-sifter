//
//  RapidEvolutionDatabaseConfigColumnsHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigColumnsHandler.h"

#include <iostream>

#include <xercesc/util/XMLString.hpp>

#include "REXML.h"

using namespace std;
using namespace xercesc;

RapidEvolutionDatabaseConfigColumnsHandler::RapidEvolutionDatabaseConfigColumnsHandler(SAX2XMLReader* parser,
                                                                                       DTAbstractHandler* parentHandler) :
DTCopyHandler::DTCopyHandler(parser, parentHandler),
qname(XMLString::transcode("columns")),
xml() {
}

void RapidEvolutionDatabaseConfigColumnsHandler::init() {
    xml.setName("columns");
    text = &xml.getXmlRef();
}

void RapidEvolutionDatabaseConfigColumnsHandler::commit() {
    REXML* dbXml = REXML::findByName("columns");
    if (dbXml->getId()) {
        if (dbXml->getXml().compare(xml.getXml())) {
            dbXml->setXml(xml.getXml());
            cout << "updating xml text for columns" << endl;
            dbXml->update();
        }
        delete dbXml;
    } else {
        xml.save();
    }
    xml.clear();
}