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

#include "DTAbstractHandler.h"
#include "Style.h"

using namespace xercesc;

RapidEvolutionDatabaseStylesStyleHandler::RapidEvolutionDatabaseStylesStyleHandler(SAX2XMLReader* parser,
                                                                                   DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
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
    startTagCount++;
    if (!XMLString::compareString(qname, getQname())) {
        const XMLCh* name_xml = attrs.getValue(name_attrib);
        const XMLCh* id_xml = attrs.getValue(id_attrib);
        style.clear();
        style.setREName(XMLString::transcode(name_xml));
        style.setREId(XMLString::parseInt(id_xml));
        std::cout << "style: " << style.getREName() << ", " << XMLString::transcode(qname) << ", " << style.getREId() << std::endl;
    }
}

void RapidEvolutionDatabaseStylesStyleHandler::endElement(const XMLCh* const uri,
                                                          const XMLCh* const localName,
                                                          const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
        Style::findStyle(&style);
        if (style.getName().length() == 0) {
            style.setName(style.getREName());
        }
        if (style.getId() > 0) {
            style.update();
        } else {
            style.save();
        }
    }
}
