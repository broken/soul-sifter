//
//  DTAbstractHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "DTAbstractHandler.h"

#include <iostream>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/util/XMLChar.hpp>

using namespace std;
using namespace xercesc;


namespace dogatech {
  
# pragma mark initialization

unsigned long DTAbstractHandler::startTagCount = 0;

DTAbstractHandler::DTAbstractHandler(SAX2XMLReader* parser, DTAbstractHandler* parentHandler) :
DefaultHandler::DefaultHandler() {
    this->childHandlers = NULL;
    this->parser = parser;
    this->parentHandler = parentHandler;
}

DTAbstractHandler::~DTAbstractHandler() {
    if (childHandlers != NULL) {
        DTAbstractHandler* handler;
        for (int i = 0; (handler = childHandlers[i]); ++i) {
            delete childHandlers[i];
        }
        delete childHandlers;
    }
}

# pragma mark xml default handler overrides

void DTAbstractHandler::startElement(const   XMLCh* const    uri,
                                     const   XMLCh* const    localname,
                                     const   XMLCh* const    qname,
                                     const   Attributes&     attrs) {
    startTagCount++;
    if (childHandlers != NULL) {
        DTAbstractHandler* handler;
        for (int i = 0; (handler = childHandlers[i]); ++i) {
            if (!XMLString::compareString(qname, handler->getQname())) {
                parser->setContentHandler(handler);
                handler->startElement(uri, localname, qname, attrs);
                break;
            }
        }
    }
}

void DTAbstractHandler::endElement(const XMLCh* const uri,
                                   const XMLCh* const localName,
                                   const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
    }
}

# pragma mark accessors

void DTAbstractHandler::characters(const XMLCh* const chars, const XMLSize_t length) {
    xercesc::DefaultHandler::characters(chars, length);
}

unsigned long DTAbstractHandler::getStartTagCount() {
    return startTagCount;
}

}