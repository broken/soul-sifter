//
//  RapidEvolutionDatabaseAbstractHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseAbstractHandler.h"

#include <iostream>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/util/XMLChar.hpp>

using namespace std;
using namespace xercesc;

# pragma mark initialization

unsigned long RapidEvolutionDatabaseAbstractHandler::startTagCount = 0;

RapidEvolutionDatabaseAbstractHandler::RapidEvolutionDatabaseAbstractHandler(SAX2XMLReader* parser,
                                                                             RapidEvolutionDatabaseAbstractHandler* parentHandler) :
DefaultHandler::DefaultHandler() {
    this->childHandlers = NULL;
    this->parser = parser;
    this->parentHandler = parentHandler;
}

RapidEvolutionDatabaseAbstractHandler::~RapidEvolutionDatabaseAbstractHandler() {
    if (childHandlers != NULL) {
        RapidEvolutionDatabaseAbstractHandler* handler;
        for (int i = 0; (handler = childHandlers[i]); ++i) {
            delete childHandlers[i];
        }
        delete childHandlers;
    }
}

# pragma mark xml default handler overrides

void RapidEvolutionDatabaseAbstractHandler::startElement(const   XMLCh* const    uri,
                                                         const   XMLCh* const    localname,
                                                         const   XMLCh* const    qname,
                                                         const   Attributes&     attrs) {
    startTagCount++;
    if (childHandlers != NULL) {
        RapidEvolutionDatabaseAbstractHandler* handler;
        for (int i = 0; (handler = childHandlers[i]); ++i) {
            if (!XMLString::compareString(qname, handler->getQname())) {
                parser->setContentHandler(handler);
                handler->startElement(uri, localname, qname, attrs);
                break;
            }
        }
    }
}

void RapidEvolutionDatabaseAbstractHandler::endElement(const XMLCh* const uri,
                                                       const XMLCh* const localName,
                                                       const XMLCh* const qName) {
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
    }
}

# pragma mark accessors

void RapidEvolutionDatabaseAbstractHandler::characters(const XMLCh* const chars, const XMLSize_t length) {
    xercesc::DefaultHandler::characters(chars, length);
}

unsigned long RapidEvolutionDatabaseAbstractHandler::getStartTagCount() {
    return startTagCount;
}