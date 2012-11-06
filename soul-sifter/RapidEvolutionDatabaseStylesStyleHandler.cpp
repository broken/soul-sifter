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
#include <xercesc/util/XMLString.hpp>

#include "RapidEvolutionDatabaseAbstractHandler.h"

using namespace xercesc;

RapidEvolutionDatabaseStylesStyleHandler::RapidEvolutionDatabaseStylesStyleHandler(SAX2XMLReader* parser,
                                                                                   RapidEvolutionDatabaseAbstractHandler* parentHandler) :
RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("style")),
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
        const XMLCh* name = attrs.getValue(name_attrib);
        char* msg = XMLString::transcode(name);
        std::cout << "style: " << msg << ", " << XMLString::transcode(qname) << std::endl;
        XMLString::release(&msg);
    }
}
