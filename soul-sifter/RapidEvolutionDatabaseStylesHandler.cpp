//
//  RapidEvolutionDatabaseStylesHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseStylesHandler.h"

#include <vector>

#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"
#include "RapidEvolutionDatabaseStylesStyleHandler.h"
#include "Style.h"

using namespace std;
using namespace xercesc;

RapidEvolutionDatabaseStylesHandler::RapidEvolutionDatabaseStylesHandler(SAX2XMLReader* parser,
                                                                         DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("styles")),
childStyles() {
    childHandlers = new DTAbstractHandler*[2];
    childHandlers[0] = new RapidEvolutionDatabaseStylesStyleHandler(parser, this, &childStyles);
    childHandlers[1] = NULL;
}

void RapidEvolutionDatabaseStylesHandler::endElement(const XMLCh* const uri,
                                                     const XMLCh* const localName,
                                                     const XMLCh* const qName) {
    // this only adds new relationships; it does not remove old ones
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
        for (vector<pair<int, int> >::iterator it = childStyles.begin(); it != childStyles.end(); ++it) {
            Style* parent = Style::findByREId(it->first);
            Style* child = Style::findByREId(it->second);
            parent->addChild(child);
        }
    }
}
