//
//  RapidEvolutionDatabaseConfigTablesHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigTablesHandler.h"

#include <iostream>

#include <xercesc/util/XMLString.hpp>

#include "REXml.h"

using namespace std;
using namespace xercesc;

namespace soulsifter {

RapidEvolutionDatabaseConfigTablesHandler::RapidEvolutionDatabaseConfigTablesHandler(SAX2XMLReader* parser,
                                                                                     DTAbstractHandler* parentHandler) :
DTCopyHandler::DTCopyHandler(parser, parentHandler),
qname(XMLString::transcode("tables")),
xml() {
}

void RapidEvolutionDatabaseConfigTablesHandler::init() {
    xml.setName("tables");
    text = &xml.getXmlRef();
}

void RapidEvolutionDatabaseConfigTablesHandler::commit() {
    REXml* dbXml = REXml::findByName("tables");
    if (dbXml) {
        if (dbXml->getXml().compare(xml.getXml())) {
            dbXml->setXml(xml.getXml());
            cout << "updating xml text for tables" << endl;
            dbXml->update();
        }
        delete dbXml;
    } else {
        xml.save();
    }
    xml.clear();
}

}
