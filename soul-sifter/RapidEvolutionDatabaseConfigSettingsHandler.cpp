//
//  RapidEvolutionDatabaseConfigSettingsHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionDatabaseConfigSettingsHandler.h"

#include <iostream>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/util/XMLString.hpp>

#include "DTAbstractHandler.h"
#include "RESetting.h"

using namespace xercesc;

RapidEvolutionDatabaseConfigSettingsHandler::RapidEvolutionDatabaseConfigSettingsHandler(SAX2XMLReader* parser,
                                                                                         DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("settings")),
reSetting(NULL) {
}

void RapidEvolutionDatabaseConfigSettingsHandler::startElement(const   XMLCh* const    uri,
                                                               const   XMLCh* const    localname,
                                                               const   XMLCh* const    qname,
                                                               const   Attributes&     attrs) {
    startTagCount++;
    if (XMLString::compareString(qname, getQname())) {
        reSetting = RESetting::findByName(XMLString::transcode(qname));
        if (!reSetting) {
            reSetting = new RESetting();
            reSetting->setName(XMLString::transcode(qname));
        }
    }
}

void RapidEvolutionDatabaseConfigSettingsHandler::endElement(const XMLCh* const uri,
                                                             const XMLCh* const localName,
                                                             const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
    } else {
        if (reSetting) {
            if (!XMLString::compareString(qName, XMLString::transcode(reSetting->getName().c_str()))) {
                if (reSetting->getId()) {
                    reSetting->update();
                } else {
                    reSetting->save();
                }
            } else {
                cout << "ERROR :: closing tag of no setting " << reSetting->getName() << " vs " << XMLString::transcode(qName) << endl;
            }
        } else {
            cout << "ERROR :: no setting to save for element " << XMLString::transcode(qName) << endl;
        }
    }
}

void RapidEvolutionDatabaseConfigSettingsHandler::characters(const XMLCh* const chars,
                                                             const XMLSize_t length) {
    if (reSetting) {
        reSetting->getValueRef().append(XMLString::transcode(chars));
    }
}

