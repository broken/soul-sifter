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

using namespace std;
using namespace xercesc;

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

void RapidEvolutionDatabaseAbstractHandler::startElement(const   XMLCh* const    uri,
                                                         const   XMLCh* const    localname,
                                                         const   XMLCh* const    qname,
                                                         const   Attributes&     attrs) {
    if (childHandlers != NULL) {
        RapidEvolutionDatabaseAbstractHandler* handler;
        for (int i = 0; (handler = childHandlers[i]); ++i) {
            if (!XMLString::compareString(qname, handler->getQname())) {
                parser->setContentHandler(handler);
                break;
            }
        }
    }
    
    char* message = XMLString::transcode(localname);
    cout << "abstract saw element: "<< message << endl;
    XMLString::release(&message);
}


void RapidEvolutionDatabaseAbstractHandler::endElement(const XMLCh* const uri,
                                                       const XMLCh* const localName,
                                                       const XMLCh* const qName) {
    if (XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
    }
}
