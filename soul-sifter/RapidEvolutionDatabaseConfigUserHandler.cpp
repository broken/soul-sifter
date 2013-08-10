//
//  RapidEvolutionDatabaseConfigUserHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigUserHandler.h"

#include <iostream>

#include <xercesc/util/XMLString.hpp>

#include "REXml.h"

using namespace std;
using namespace xercesc;

namespace dogatech {
namespace soulsifter {
    
RapidEvolutionDatabaseConfigUserHandler::RapidEvolutionDatabaseConfigUserHandler(SAX2XMLReader* parser,
                                                                                 DTAbstractHandler* parentHandler) :
DTCopyHandler::DTCopyHandler(parser, parentHandler),
qname(XMLString::transcode("user")),
xml() {
}

void RapidEvolutionDatabaseConfigUserHandler::init() {
    xml.setName("user");
    text = &xml.getXmlRef();
}

void RapidEvolutionDatabaseConfigUserHandler::commit() {
    REXml* dbXml = REXml::findByName("user");
    if (dbXml) {
        if (dbXml->getXml().compare(xml.getXml())) {
            dbXml->setXml(xml.getXml());
            cout << "updating xml text for user" << endl;
            dbXml->update();
        }
        delete dbXml;
    } else {
        xml.save();
    }
    xml.clear();
}
    
}
}
