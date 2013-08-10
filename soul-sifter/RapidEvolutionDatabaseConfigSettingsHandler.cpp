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

namespace dogatech {
namespace soulsifter {

RapidEvolutionDatabaseConfigSettingsHandler::RapidEvolutionDatabaseConfigSettingsHandler(SAX2XMLReader* parser,
                                                                                         DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("settings")),
reSetting(),
searchHistoryLabel("search_history_") {
}

void RapidEvolutionDatabaseConfigSettingsHandler::startElement(const   XMLCh* const    uri,
                                                               const   XMLCh* const    localname,
                                                               const   XMLCh* const    qname,
                                                               const   Attributes&     attrs) {
    startTagCount++;
    if (XMLString::compareString(qname, getQname())) {
        reSetting.setName(XMLString::transcode(qname));
    }
}

void RapidEvolutionDatabaseConfigSettingsHandler::endElement(const XMLCh* const uri,
                                                             const XMLCh* const localName,
                                                             const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
    } else {
        if (reSetting.getName().length() > 0) {
            if (!XMLString::compareString(qName, XMLString::transcode(reSetting.getName().c_str()))) {
                // don't save the search history since it changes so often
                if (reSetting.getName().compare(0, searchHistoryLabel.length(), searchHistoryLabel)) {
                    RESetting* dbSetting = RESetting::findByName(reSetting.getName());
                    if (dbSetting) {
                        if (dbSetting->getValue().compare(reSetting.getValue())) {
                            cout << "updating setting " << reSetting.getName() << " from " << dbSetting->getValue() << " to " << reSetting.getValue() << endl;
                            dbSetting->setValue(reSetting.getValue());
                            dbSetting->update();
                        }
                        delete dbSetting;
                    } else {
                        reSetting.save();
                    }
                }
            } else {
                cout << "ERROR: closing tag of no setting " << reSetting.getName() << " vs " << XMLString::transcode(qName) << endl;
            }
            reSetting.clear();
        } else {
            cout << "ERROR: no setting to save for element " << XMLString::transcode(qName) << endl;
        }
    }
}

void RapidEvolutionDatabaseConfigSettingsHandler::characters(const XMLCh* const chars,
                                                             const XMLSize_t length) {
    if (reSetting.getName().length() > 0) {
        reSetting.getValueRef().append(XMLString::transcode(chars));
    }
}

}
}
