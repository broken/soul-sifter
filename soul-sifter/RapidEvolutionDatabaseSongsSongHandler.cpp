//
//  RapidEvolutionDatabaseSongsSongHandler.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#include "RapidEvolutionDatabaseSongsSongHandler.h"

#include <iostream>

#include <boost/any.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include "DTAbstractHandler.h"
#include "RESong.h"

using namespace std;
using namespace xercesc;

RapidEvolutionDatabaseSongsSongHandler::RapidEvolutionDatabaseSongsSongHandler(SAX2XMLReader* parser,
                                                                               DTAbstractHandler* parentHandler) :
DTAbstractHandler::DTAbstractHandler(parser, parentHandler),
qname(XMLString::transcode("song")),
song(),
fieldPointer(NULL),
unique_id_elem(XMLString::transcode("unique_id")),
songid_winfo_elem(XMLString::transcode("songid_winfo")),
songid_elem(XMLString::transcode("songid")),
shortid_elem(XMLString::transcode("shortid")),
shortid_winfo_elem(XMLString::transcode("shortid_winfo")),
artist_elem(XMLString::transcode("artist")),
album_elem(XMLString::transcode("album")),
track_elem(XMLString::transcode("track")),
title_elem(XMLString::transcode("title")),
time_elem(XMLString::transcode("time")),
time_signature_elem(XMLString::transcode("time_signature")),
filename_elem(XMLString::transcode("filename")),
digital_only_elem(XMLString::transcode("digital_only")),
compilation_elem(XMLString::transcode("compilation")),
key_start_elem(XMLString::transcode("key_start")),
key_accuracy_elem(XMLString::transcode("key_accuracy")),
bpm_start_elem(XMLString::transcode("bpm_start")),
bpm_accuracy_elem(XMLString::transcode("bpm_accuracy")),
rating_elem(XMLString::transcode("rating")),
date_added_elem(XMLString::transcode("date_added")),
catalog_id_elem(XMLString::transcode("custom4")),
label_elem(XMLString::transcode("custom3")),
remix_elem(XMLString::transcode("remix")),
num_plays_elem(XMLString::transcode("num_plays")),
comments_elem(XMLString::transcode("comments")),
release_date_elem(XMLString::transcode("custom2")),
featuring_elem(XMLString::transcode("custom1")),
key_end_elem(XMLString::transcode("key_end")),
disabled_elem(XMLString::transcode("disabled")),
bpm_end_elem(XMLString::transcode("bpm_end")),
beat_intensity_elem(XMLString::transcode("beat_intensity")),
replay_gain_elem(XMLString::transcode("replay_gain")),
styles_bitmask_elem(XMLString::transcode("styles_bitmask")) {
}

void RapidEvolutionDatabaseSongsSongHandler::startElement(const   XMLCh* const    uri,
                                                          const   XMLCh* const    localname,
                                                          const   XMLCh* const    qname,
                                                          const   Attributes&     attrs) {
    startTagCount++;
    if (!XMLString::compareString(qname, getQname())) {
        song.clear();
        fieldPointer = NULL;
    } else if (!XMLString::compareString(qname, unique_id_elem)) {
        fieldPointer = &song.unique_id;
    } else if (!XMLString::compareString(qname, songid_winfo_elem)) {
        fieldPointer = &song.songid_winfo;
    } else if (!XMLString::compareString(qname, songid_elem)) {
        fieldPointer = &song.songid;
    } else if (!XMLString::compareString(qname, shortid_elem)) {
        fieldPointer = &song.shortid;
    } else if (!XMLString::compareString(qname, shortid_winfo_elem)) {
        fieldPointer = &song.shortid_winfo;
    } else if (!XMLString::compareString(qname, artist_elem)) {
        fieldPointer = &song.artist;
    } else if (!XMLString::compareString(qname, album_elem)) {
        fieldPointer = &song.album;
    } else if (!XMLString::compareString(qname, track_elem)) {
        fieldPointer = &song.track;
    } else if (!XMLString::compareString(qname, title_elem)) {
        fieldPointer = &song.title;
    } else if (!XMLString::compareString(qname, time_elem)) {
        fieldPointer = &song.time;
    } else if (!XMLString::compareString(qname, time_signature_elem)) {
        fieldPointer = &song.time_signature;
    } else if (!XMLString::compareString(qname, filename_elem)) {
        fieldPointer = &song.filename;
    } else if (!XMLString::compareString(qname, digital_only_elem)) {
        fieldPointer = &song.digital_only;
    } else if (!XMLString::compareString(qname, compilation_elem)) {
        fieldPointer = &song.compilation;
    } else if (!XMLString::compareString(qname, key_start_elem)) {
        fieldPointer = &song.key_start;
    } else if (!XMLString::compareString(qname, key_accuracy_elem)) {
        fieldPointer = &song.key_accuracy;
    } else if (!XMLString::compareString(qname, bpm_start_elem)) {
        fieldPointer = &song.bpm_start;
    } else if (!XMLString::compareString(qname, bpm_accuracy_elem)) {
        fieldPointer = &song.bpm_accuracy;
    } else if (!XMLString::compareString(qname, rating_elem)) {
        fieldPointer = &song.rating;
    } else if (!XMLString::compareString(qname, date_added_elem)) {
        fieldPointer = &song.date_added;
    } else if (!XMLString::compareString(qname, catalog_id_elem)) {
        fieldPointer = &song.catalog_id;
    } else if (!XMLString::compareString(qname, label_elem)) {
        fieldPointer = &song.label;
    } else if (!XMLString::compareString(qname, remix_elem)) {
        fieldPointer = &song.remix;
    } else if (!XMLString::compareString(qname, num_plays_elem)) {
        fieldPointer = &song.num_plays;
    } else if (!XMLString::compareString(qname, comments_elem)) {
        fieldPointer = &song.comments;
    } else if (!XMLString::compareString(qname, release_date_elem)) {
        fieldPointer = &song.release_date;
    } else if (!XMLString::compareString(qname, featuring_elem)) {
        fieldPointer = &song.featuring;
    } else if (!XMLString::compareString(qname, key_end_elem)) {
        fieldPointer = &song.key_end;
    } else if (!XMLString::compareString(qname, disabled_elem)) {
        fieldPointer = &song.disabled;
    } else if (!XMLString::compareString(qname, bpm_end_elem)) {
        fieldPointer = &song.bpm_end;
    } else if (!XMLString::compareString(qname, beat_intensity_elem)) {
        fieldPointer = &song.beat_intensity;
    } else if (!XMLString::compareString(qname, replay_gain_elem)) {
        fieldPointer = &song.replay_gain;
    } else if (!XMLString::compareString(qname, styles_bitmask_elem)) {
        fieldPointer = &song.styles_bitmask;
    } else {
        cout << "ERROR:: no album processor for " << XMLString::transcode(qname) << endl;
    }
}

void RapidEvolutionDatabaseSongsSongHandler::endElement(const XMLCh* const uri,
                                                        const XMLCh* const localName,
                                                        const XMLCh* const qName) {
    fieldPointer = NULL;
    if (!XMLString::compareString(qName, getQname()) && parentHandler != NULL) {
        parser->setContentHandler(parentHandler);
        if (RESong::lookup(&song)) {
            song.update();
        } else {
            song.save();
        }
    }
}

void RapidEvolutionDatabaseSongsSongHandler::characters(const XMLCh* const chars,
                                                        const XMLSize_t length) {
    if (fieldPointer.type() == typeid(int*)) {
        *(boost::any_cast<int*>(fieldPointer)) = XMLString::parseInt(chars);
    } else if (fieldPointer.type() == typeid(std::string*)) {
        boost::any_cast<std::string*>(fieldPointer)->append(XMLString::transcode(chars));
    } else if (fieldPointer.type() == typeid(double*)) {
        *(boost::any_cast<double*>(fieldPointer)) = atof(XMLString::transcode(chars));
    }
}