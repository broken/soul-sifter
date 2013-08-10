//
//  DTCopyHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "DTCopyHandler.h"

#include <string>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/util/XMLString.hpp>

#include "DTAbstractHandler.h"

using namespace std;
using namespace xercesc;

namespace dogatech {
  
DTCopyHandler::DTCopyHandler(SAX2XMLReader* parser,
                             DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
text(),
data(false) {
}

void DTCopyHandler::startElement(const XMLCh* const uri,
                                 const XMLCh* const localname,
                                 const XMLCh* const qname,
                                 const xercesc::Attributes& attrs) {
    startTagCount++;
    if (!XMLString::compareString(getQname(), qname)) {
        init();
    }
    text->append("<").append(XMLString::transcode(qname));
    for (int i = 0; i < attrs.getLength(); ++i) {
        text->append(" ").append(XMLString::transcode(attrs.getQName(i)));
        text->append("=\"").append(XMLString::transcode(attrs.getValue(i))).append("\"");
    }
    data = false;
}

void DTCopyHandler::endElement(const XMLCh* const uri,
                               const XMLCh* const localName,
                               const XMLCh* const qname) {
    if (data) {
        text->append("</").append(XMLString::transcode(qname)).append(">");
        if (!XMLString::compareString(getQname(), qname)) {
            parser->setContentHandler(parentHandler);
            text->append("\n");
            commit();
        }
    } else {
        text->append("/>");
        data = true;
    }
}

void DTCopyHandler::characters(const XMLCh* const chars, const XMLSize_t length) {
    if (!data) {
        data = true;
        text->append(">");
    }
    text->append(XMLString::transcode(chars));
}
  
}
