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

#include "REXml.h"

using namespace std;
using namespace xercesc;

namespace soulsifter {

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
    REXml* dbXml = REXml::findByName("columns");
    if (dbXml) {
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

}
