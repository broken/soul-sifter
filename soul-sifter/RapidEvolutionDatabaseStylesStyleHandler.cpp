//
//  RapidEvolutionDatabaseStylesStyleHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseStylesStyleHandler.h"

#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/util/XMLString.hpp>

#include "DTAbstractHandler.h"
#include "Style.h"

using namespace xercesc;

namespace soulsifter {

RapidEvolutionDatabaseStylesStyleHandler::RapidEvolutionDatabaseStylesStyleHandler(SAX2XMLReader* parser,
                                                                                   DTAbstractHandler* parentHandler,
                                                                                   vector<pair<int, int> >* styles) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("style")),
style(),
childStyles(styles),
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
        const XMLCh* child_ids_xml = attrs.getValue(child_ids_attrib);
        style.clear();
        style.setRELabel(XMLString::transcode(name_xml));
        style.setREId(XMLString::parseInt(id_xml));
        string ids = XMLString::transcode(child_ids_xml);
        if (!ids.empty()) {
            vector<string> children;
            boost::split(children, ids, boost::is_any_of(","));
            for (vector<string>::iterator it = children.begin(); it != children.end(); ++it) {
                pair<int, int> relationship(style.getREId(), atoi((*it).c_str()));
                childStyles->push_back(relationship);
            }
        }
    }
}

void RapidEvolutionDatabaseStylesStyleHandler::endElement(const XMLCh* const uri,
                                                          const XMLCh* const localName,
                                                          const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
        if (style.sync()) {
            if (style.getId()) {
                style.update();
            } else {
                if (style.getName().length() == 0) {
                    style.setName(style.getRELabel());
                }
                style.save();
            }
        }
    }
}

}
