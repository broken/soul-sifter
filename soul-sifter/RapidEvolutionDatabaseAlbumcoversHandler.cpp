//
//  RapidEvolutionDatabaseAlbumcoversHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseAlbumcoversHandler.h"

#include <iostream>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/util/XMLString.hpp>

#include "DTAbstractHandler.h"
#include "REAlbumCover.h"

using namespace xercesc;

namespace dogatech {
namespace soulsifter {

RapidEvolutionDatabaseAlbumcoversHandler::RapidEvolutionDatabaseAlbumcoversHandler(SAX2XMLReader* parser,
                                                                                   DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("albumcovers")),
acQname(XMLString::transcode("albumcover")),
albumcover(NULL),
id_attrib(XMLString::transcode("id")),
thumbnail_attrib(XMLString::transcode("thumbnail")) {
}

void RapidEvolutionDatabaseAlbumcoversHandler::startElement(const   XMLCh* const    uri,
                                                            const   XMLCh* const    localname,
                                                            const   XMLCh* const    qname,
                                                            const   Attributes&     attrs) {
    startTagCount++;
    if (!XMLString::compareString(acQname, qname)) {
        const XMLCh* id_xml = attrs.getValue(id_attrib);
        const XMLCh* tn_xml = attrs.getValue(thumbnail_attrib);
        string reId = XMLString::transcode(id_xml);
        albumcover = REAlbumCover::findByREId(reId);
        if (!albumcover) {
            albumcover = new REAlbumCover();
            albumcover->setREId(reId);
        }
        albumcover->setThumbnail(XMLString::transcode(tn_xml));
    }
}

void RapidEvolutionDatabaseAlbumcoversHandler::endElement(const XMLCh* const uri,
                                                          const XMLCh* const localName,
                                                          const XMLCh* const qname) {
    if (!XMLString::compareString(qname, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
    } else if (!XMLString::compareString(qname, acQname)) {
        if (albumcover->getId()) {
            albumcover->update();
        } else {
            albumcover->save();
        }
        delete albumcover;
        albumcover = NULL;
    }
}
    
}
}
