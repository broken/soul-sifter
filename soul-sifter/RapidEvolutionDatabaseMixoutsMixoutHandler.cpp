//
//  RapidEvolutionDatabaseMixoutsMixoutHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/3/12.
//
//

#include "RapidEvolutionDatabaseMixoutsMixoutHandler.h"

#include <iostream>

#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"
#include "Mix.h"

using namespace std;
using namespace xercesc;

namespace soulsifter {

RapidEvolutionDatabaseMixoutsMixoutHandler::RapidEvolutionDatabaseMixoutsMixoutHandler(SAX2XMLReader* parser,
                                                                                       DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("mixout")),
mix(),
fieldPointer(NULL),
addonStr(),
from_unique_id_elem(XMLString::transcode("from_unique_id")),
to_unique_id_elem(XMLString::transcode("to_unique_id")),
bpm_diff_elem(XMLString::transcode("bpm_diff")),
rank_elem(XMLString::transcode("rank")),
comments_elem(XMLString::transcode("comments")),
addon_elem(XMLString::transcode("addon")) {
}

void RapidEvolutionDatabaseMixoutsMixoutHandler::startElement(const   XMLCh* const    uri,
                                                              const   XMLCh* const    localname,
                                                              const   XMLCh* const    qname,
                                                              const   Attributes&     attrs) {
    startTagCount++;
    if (!XMLString::compareString(qname, getQname())) {
        mix.clear();
        addonStr.clear();
    } else if (!XMLString::compareString(qname, from_unique_id_elem)) {
        fieldPointer = &mix.outSongId;
    } else if (!XMLString::compareString(qname, to_unique_id_elem)) {
        fieldPointer = &mix.inSongId;
    } else if (!XMLString::compareString(qname, bpm_diff_elem)) {
        fieldPointer = &mix.bpmDiff;
    } else if (!XMLString::compareString(qname, rank_elem)) {
        fieldPointer = &mix.rank;
    } else if (!XMLString::compareString(qname, comments_elem)) {
        fieldPointer = &mix.comments;
    } else if (!XMLString::compareString(qname, addon_elem)) {
        fieldPointer = &addonStr;
    } else {
        cout << "ERROR: no mixout processor for " << XMLString::transcode(qname) << endl;
    }
}

void RapidEvolutionDatabaseMixoutsMixoutHandler::endElement(const XMLCh* const uri,
                                                            const XMLCh* const localName,
                                                            const XMLCh* const qname) {
    fieldPointer = NULL;
    if (!XMLString::compareString(qname, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
        
        mix.setAddon(!addonStr.compare("yes"));
        Song* outSong = Song::findByRESongId(mix.outSongId);
        mix.setOutSong(outSong);
        Song* inSong = Song::findByRESongId(mix.inSongId);
        mix.setInSong(inSong);
        
        // TODO currently this is limited to 1 mix per song pair. would be great to allow multiple.
        Mix* dbMix = Mix::findBySongIds(outSong->getId(), inSong->getId());
        if (dbMix) {
            bool needsUpdating = false;
            if (dbMix->getAddon() != mix.getAddon()) {
                needsUpdating = true;
                dbMix->setAddon(mix.getAddon());
                cout << "updating mix " << dbMix->getId() << " addon from " << dbMix->getAddon() << " to " << mix.getAddon() << endl;
            }
            if (dbMix->getBPMDiff().compare(0, mix.getBPMDiff().size(), mix.getBPMDiff()) &&
                (mix.getBPMDiff().compare(0, dbMix->getBPMDiff().size()-1, dbMix->getBPMDiff()) || dbMix->getBPMDiff().size() < 4)) {
                needsUpdating = true;
                dbMix->setBPMDiff(mix.getBPMDiff());
                cout << "updating mix " << dbMix->getId() << " bpm diff from " << dbMix->getBPMDiff() << " to " << mix.getBPMDiff() << endl;
            }
            if (dbMix->getRank() != mix.getRank()) {
                needsUpdating = true;
                dbMix->setRank(mix.getRank());
                cout << "updating mix " << dbMix->getId() << " rank from " << dbMix->getRank() << " to " << mix.getRank() << endl;
            }
            if (dbMix->getComments().compare(mix.getComments())) {
                needsUpdating = true;
                dbMix->setComments(mix.getComments());
                cout << "updating mix " << dbMix->getId() << " comments from " << dbMix->getComments() << " to " << mix.getComments() << endl;
            }
            if (needsUpdating)
                dbMix->update();
        } else {
            mix.save();
        }
    }
}

void RapidEvolutionDatabaseMixoutsMixoutHandler::characters(const XMLCh* const chars,
                                                            const XMLSize_t length) {
    if (fieldPointer.type() == typeid(int*)) {
        *(boost::any_cast<int*>(fieldPointer)) = XMLString::parseInt(chars);
    } else if (fieldPointer.type() == typeid(std::string*)) {
        boost::any_cast<std::string*>(fieldPointer)->append(XMLString::transcode(chars));
    } else if (fieldPointer.type() == typeid(double*)) {
        *(boost::any_cast<double*>(fieldPointer)) = atof(XMLString::transcode(chars));
    }
}
    
}
