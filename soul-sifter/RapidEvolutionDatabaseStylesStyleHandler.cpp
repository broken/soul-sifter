//
//  RapidEvolutionDatabaseStylesStyleHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseStylesStyleHandler.h"

#include <iostream>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/util/XMLString.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"
#include "Style.h"

using namespace xercesc;

RapidEvolutionDatabaseStylesStyleHandler::RapidEvolutionDatabaseStylesStyleHandler(SAX2XMLReader* parser,
                                                                                   RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("style")),
style(),
category_only_attrib(XMLString::transcode("category_only")),
child_ids_attrib(XMLString::transcode("child_ids")),
description_attrib(XMLString::transcode("description")),
id_attrib(XMLString::transcode("id")),
name_attrib(XMLString::transcode("name")),
parent_ids_attrib(XMLString::transcode("parent_ids")) {
}

void RapidEvolutionDatabaseStylesStyleHandler::startElement(const   XMLCh* const    uri,
                                                            const   XMLCh* const    localname,
                                                            const   XMLCh* const    qname,
                                                            const   Attributes&     attrs) {
    if (!XMLString::compareString(qname, getQname())) {
        const XMLCh* name_xml = attrs.getValue(name_attrib);
        const XMLCh* id_xml = attrs.getValue(id_attrib);
        style.clear();
        style.re_name = XMLString::transcode(name_xml);
        style.re_id = XMLString::parseInt(id_xml);
        std::cout << "style: " << style.re_name << ", " << XMLString::transcode(qname) << ", " << style.re_id << std::endl;
    }
}

void RapidEvolutionDatabaseStylesStyleHandler::endElement(const XMLCh* const uri,
                                                          const XMLCh* const localName,
                                                          const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
        Style::findStyle(&style);
        if (style.name.length() == 0) {
            style.name = style.re_name;
        }
        if (style.id > 0) {
            bool success = style.update();
            cout << "update style. success = " << success << endl;
        } else {
            bool success = style.save();
            cout << "update style. success = " << success << endl;
        }
    }
}
