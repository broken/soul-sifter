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
#include "Song.h"

using namespace std;
using namespace xercesc;

namespace soulsifter {

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
        RESong *dbSong = RESong::findByUniqueId(song.getUniqueId());
        if (dbSong) {
            bool needsUpdating = false;
            if (dbSong->getAlbum().compare(song.getAlbum())) {
                needsUpdating = true;
                dbSong->setAlbum(song.getAlbum());
                cout << "updating re song " << dbSong->getUniqueId() << " album from " << dbSong->getAlbum() << " to " << song.getAlbum() << endl;
            }
            if (dbSong->getArtist().compare(song.getArtist())) {
                needsUpdating = true;
                dbSong->setArtist(song.getArtist());
                cout << "updating re song " << dbSong->getUniqueId() << " artist from " << dbSong->getArtist() << " to " << song.getArtist() << endl;
            }
            if (dbSong->getBeatIntensity() != song.getBeatIntensity()) {
                needsUpdating = true;
                dbSong->setBeatIntensity(song.getBeatIntensity());
                cout << "updating re song " << dbSong->getUniqueId() << " beat intensity from " << dbSong->getBeatIntensity() << " to " << song.getBeatIntensity() << endl;
            }
            if (dbSong->getBPMAccuracy() != song.getBPMAccuracy()) {
                needsUpdating = true;
                dbSong->setBPMAccuracy(song.getBPMAccuracy());
                cout << "updating re song " << dbSong->getUniqueId() << " bpm accuracy from " << dbSong->getBPMAccuracy() << " to " << song.getBPMAccuracy() << endl;
            }
            if (dbSong->getBPMEnd().compare(0, song.getBPMEnd().size(), song.getBPMEnd()) &&
                (song.getBPMEnd().compare(0, dbSong->getBPMEnd().size()-1, dbSong->getBPMEnd()) || dbSong->getBPMEnd().size() < 4)) {
                needsUpdating = true;
                dbSong->setBPMEnd(song.getBPMEnd());
                cout << "updating re song " << dbSong->getUniqueId() << " bpm end from " << dbSong->getBPMEnd() << " to " << song.getBPMEnd() << endl;
            }
            if (dbSong->getBPMStart().compare(0, song.getBPMStart().size(), song.getBPMStart()) &&
                (song.getBPMStart().compare(0, dbSong->getBPMStart().size()-1, dbSong->getBPMStart()) || dbSong->getBPMStart().size() < 4)) {
                needsUpdating = true;
                dbSong->setBPMStart(song.getBPMStart());
                cout << "updating re song " << dbSong->getUniqueId() << " bpm start from " << dbSong->getBPMStart() << " to " << song.getBPMStart() << endl;
            }
            if (dbSong->getCatalogId().compare(song.getCatalogId())) {
                needsUpdating = true;
                dbSong->setCatalogId(song.getCatalogId());
                cout << "updating re song " << dbSong->getUniqueId() << " catalog id from " << dbSong->getCatalogId() << " to " << song.getCatalogId() << endl;
            }
            if (dbSong->getComments().compare(song.getComments())) {
                needsUpdating = true;
                dbSong->setComments(song.getComments());
                cout << "updating re song " << dbSong->getUniqueId() << " comments from " << dbSong->getComments() << " to " << song.getComments() << endl;
            }
            if (dbSong->getCompilation().compare(song.getCompilation())) {
                needsUpdating = true;
                dbSong->setCompilation(song.getCompilation());
                cout << "updating re song " << dbSong->getUniqueId() << " compilation from " << dbSong->getCompilation() << " to " << song.getCompilation() << endl;
            }
            if (dbSong->getDateAdded().compare(song.getDateAdded())) {
                needsUpdating = true;
                dbSong->setDateAdded(song.getDateAdded());
                cout << "updating re song " << dbSong->getUniqueId() << " date added from " << dbSong->getDateAdded() << " to " << song.getDateAdded() << endl;
            }
            if (dbSong->getDigitalOnly().compare(song.getDigitalOnly())) {
                needsUpdating = true;
                dbSong->setDigitalOnly(song.getDigitalOnly());
                cout << "updating re song " << dbSong->getUniqueId() << " digital only from " << dbSong->getDigitalOnly() << " to " << song.getDigitalOnly() << endl;
            }
            if (dbSong->getDisabled().compare(song.getDisabled())) {
                needsUpdating = true;
                dbSong->setDisabled(song.getDisabled());
                cout << "updating re song " << dbSong->getUniqueId() << " disabled from " << dbSong->getDisabled() << " to " << song.getDisabled() << endl;
            }
            if (dbSong->getFeaturing().compare(song.getFeaturing())) {
                needsUpdating = true;
                dbSong->setFeaturing(song.getFeaturing());
                cout << "updating re song " << dbSong->getUniqueId() << " featuring from " << dbSong->getFeaturing() << " to " << song.getFeaturing() << endl;
            }
            if (dbSong->getFilename().compare(song.getFilename())) {
                needsUpdating = true;
                dbSong->setFilename(song.getFilename());
                cout << "updating re song " << dbSong->getUniqueId() << " filename from " << dbSong->getFilename() << " to " << song.getFilename() << endl;
            }
            if (dbSong->getKeyAccuracy() != song.getKeyAccuracy()) {
                needsUpdating = true;
                dbSong->setKeyAccuracy(song.getKeyAccuracy());
                cout << "updating re song " << dbSong->getUniqueId() << " key accuracy from " << dbSong->getKeyAccuracy() << " to " << song.getKeyAccuracy() << endl;
            }
            if (dbSong->getKeyEnd().compare(song.getKeyEnd())) {
                needsUpdating = true;
                dbSong->setKeyEnd(song.getKeyEnd());
                cout << "updating re song " << dbSong->getUniqueId() << " key end from " << dbSong->getKeyEnd() << " to " << song.getKeyEnd() << endl;
            }
            if (dbSong->getKeyStart().compare(song.getKeyStart())) {
                needsUpdating = true;
                dbSong->setKeyStart(song.getKeyStart());
                cout << "updating re song " << dbSong->getUniqueId() << " key start from " << dbSong->getKeyStart() << " to " << song.getKeyStart() << endl;
            }
            if (dbSong->getLabel().compare(song.getLabel())) {
                needsUpdating = true;
                dbSong->setLabel(song.getLabel());
                cout << "updating re song " << dbSong->getUniqueId() << " label from " << dbSong->getLabel() << " to " << song.getLabel() << endl;
            }
            if (dbSong->getNumPlays() != song.getNumPlays()) {
                needsUpdating = true;
                dbSong->setNumPlays(song.getNumPlays());
                cout << "updating re song " << dbSong->getUniqueId() << " num plays from " << dbSong->getNumPlays() << " to " << song.getNumPlays() << endl;
            }
            if (dbSong->getRating() != song.getRating()) {
                needsUpdating = true;
                dbSong->setRating(song.getRating());
                cout << "updating re song " << dbSong->getUniqueId() << " rating from " << dbSong->getRating() << " to " << song.getRating() << endl;
            }
            if (dbSong->getReleaseDate().compare(song.getReleaseDate())) {
                needsUpdating = true;
                dbSong->setReleaseDate(song.getReleaseDate());
                cout << "updating re song " << dbSong->getUniqueId() << " release date from " << dbSong->getReleaseDate() << " to " << song.getReleaseDate() << endl;
            }
            if (dbSong->getRemix().compare(song.getRemix())) {
                needsUpdating = true;
                dbSong->setRemix(song.getRemix());
                cout << "updating re song " << dbSong->getUniqueId() << " remix from " << dbSong->getRemix() << " to " << song.getRemix() << endl;
            }
            if (dbSong->getReplayGain().compare(song.getReplayGain())) {
                needsUpdating = true;
                dbSong->setReplayGain(song.getReplayGain());
                cout << "updating re song " << dbSong->getUniqueId() << " replay gain from " << dbSong->getReplayGain() << " to " << song.getReplayGain() << endl;
            }
            if (dbSong->getShortId().compare(song.getShortId())) {
                needsUpdating = true;
                dbSong->setShortId(song.getShortId());
                cout << "updating re song " << dbSong->getUniqueId() << " short id from " << dbSong->getShortId() << " to " << song.getShortId() << endl;
            }
            if (dbSong->getShortIdWInfo().compare(song.getShortIdWInfo())) {
                needsUpdating = true;
                dbSong->setShortIdWInfo(song.getShortIdWInfo());
                cout << "updating re song " << dbSong->getUniqueId() << " short id w/ info from " << dbSong->getShortIdWInfo() << " to " << song.getShortIdWInfo() << endl;
            }
            if (dbSong->getSongId().compare(song.getSongId())) {
                needsUpdating = true;
                dbSong->setSongId(song.getSongId());
                cout << "updating re song " << dbSong->getUniqueId() << " song id from " << dbSong->getSongId() << " to " << song.getSongId() << endl;
            }
            if (dbSong->getSongIdWInfo().compare(song.getSongIdWInfo())) {
                needsUpdating = true;
                dbSong->setSongIdWInfo(song.getSongIdWInfo());
                cout << "updating re song " << dbSong->getUniqueId() << " song id w/ info from " << dbSong->getSongIdWInfo() << " to " << song.getSongIdWInfo() << endl;
            }
            if (dbSong->getStylesBitmask().compare(song.getStylesBitmask())) {
                needsUpdating = true;
                dbSong->setStylesBitmask(song.getStylesBitmask());
                cout << "updating re song " << dbSong->getUniqueId() << " styles bitmask from " << dbSong->getStylesBitmask() << " to " << song.getStylesBitmask() << endl;
            }
            if (dbSong->getTime().compare(song.getTime())) {
                needsUpdating = true;
                dbSong->setTime(song.getTime());
                cout << "updating re song " << dbSong->getUniqueId() << " time from " << dbSong->getTime() << " to " << song.getTime() << endl;
            }
            if (dbSong->getTimeSignature().compare(song.getTimeSignature())) {
                needsUpdating = true;
                dbSong->setTimeSignature(song.getTimeSignature());
                cout << "updating re song " << dbSong->getUniqueId() << " time signature from " << dbSong->getTimeSignature() << " to " << song.getTimeSignature() << endl;
            }
            if (dbSong->getTitle().compare(song.getTitle())) {
                needsUpdating = true;
                dbSong->setTitle(song.getTitle());
                cout << "updating re song " << dbSong->getUniqueId() << " title from " << dbSong->getTitle() << " to " << song.getTitle() << endl;
            }
            if (dbSong->getTrack().compare(song.getTrack())) {
                needsUpdating = true;
                dbSong->setTrack(song.getTrack());
                cout << "updating re song " << dbSong->getUniqueId() << " track from " << dbSong->getTrack() << " to " << song.getTrack() << endl;
            }
            if (needsUpdating)
                dbSong->update();
            
            Song *mySong = Song::findByRESongId(dbSong->getUniqueId());
            if (mySong) {
                bool songNeedsUpdating = false;
                bool albumNeedsUpdating = false;
                Album *album = mySong->getAlbum();
                // TODO update album basic genre? would depend on filepath
                if (album->getCatalogId().compare(song.getCatalogId())) {
                    albumNeedsUpdating = true;
                    album->setCatalogId(song.getCatalogId());
                    cout << "updating album " << album->getId() << " catalog id from " << album->getCatalogId() << " to " << song.getCatalogId() << endl;
                }
                if (album->getLabel().compare(song.getLabel())) {
                    albumNeedsUpdating = true;
                    album->setLabel(song.getLabel());
                    cout << "updating album " << album->getId() << " label from " << album->getLabel() << " to " << song.getLabel() << endl;
                }
                if (album->getName().compare(song.getAlbum()) && album->getName().size() > 0) {
                    albumNeedsUpdating = true;
                    album->setName(song.getAlbum());
                    cout << "updating album " << album->getId() << " name from " << album->getName() << " to " << song.getAlbum() << endl;
                }
                if (song.getReleaseDate().size() >= 4 && album->getReleaseDateYear() != atoi(song.getReleaseDate().substr(0,4).c_str())) {
                    albumNeedsUpdating = true;
                    album->setReleaseDateYear(atoi(song.getReleaseDate().substr(0,4).c_str()));
                    cout << "updating album " << album->getId() << " release date year " << album->getReleaseDateYear() << " to " << song.getReleaseDate().substr(0,4) << endl;
                } else if (song.getReleaseDate().size() < 6 && album->getReleaseDateYear()) {
                    albumNeedsUpdating = true;
                    album->setReleaseDateYear(0);
                    cout << "updating album " << album->getId() << " release date year " << album->getReleaseDateYear() << " to 0 (" << song.getReleaseDate() << ") " << endl;
                }
                if (song.getReleaseDate().size() >= 6 && album->getReleaseDateMonth() != atoi(song.getReleaseDate().substr(4,2).c_str())) {
                    albumNeedsUpdating = true;
                    album->setReleaseDateMonth(atoi(song.getReleaseDate().substr(4,2).c_str()));
                    cout << "updating album " << album->getId() << " release date month " << album->getReleaseDateMonth() << " to " << song.getReleaseDate().substr(4,2) << endl;
                } else if (song.getReleaseDate().size() < 6 && album->getReleaseDateMonth()) {
                    albumNeedsUpdating = true;
                    album->setReleaseDateMonth(0);
                    cout << "updating album " << album->getId() << " release date month " << album->getReleaseDateMonth() << " to 0 (" << song.getReleaseDate() << ") " << endl;
                }
                if (song.getReleaseDate().size() >= 8 && album->getReleaseDateDay() != atoi(song.getReleaseDate().substr(6,2).c_str())) {
                    albumNeedsUpdating = true;
                    album->setReleaseDateDay(atoi(song.getReleaseDate().substr(6,2).c_str()));
                    cout << "updating album " << album->getId() << " release date day " << album->getReleaseDateDay() << " to " << song.getReleaseDate().substr(6,2) << endl;
                } else if (song.getReleaseDate().size() < 8 && album->getReleaseDateDay()) {
                    albumNeedsUpdating = true;
                    album->setReleaseDateDay(0);
                    cout << "updating album " << album->getId() << " release date day " << album->getReleaseDateDay() << " to 0 (" << song.getReleaseDate() << ") " << endl;
                }
                // TODO update styles
                // TODO update date added. should I even worry about this one?
                if (mySong->getArtist().compare(song.getArtist())) {
                    songNeedsUpdating = true;
                    mySong->setArtist(song.getArtist());
                    cout << "updating song " << mySong->getId() << " artist from " << mySong->getArtist() << " to " << song.getArtist() << endl;
                }
                if (mySong->getComments().compare(song.getComments())) {
                    songNeedsUpdating = true;
                    mySong->setComments(song.getComments());
                    cout << "updating song " << mySong->getId() << " comments from " << mySong->getComments() << " to " << song.getComments() << endl;
                }
                if (mySong->getFeaturing().compare(song.getFeaturing())) {
                    songNeedsUpdating = true;
                    mySong->setFeaturing(song.getFeaturing());
                    cout << "updating song " << mySong->getId() << " featuring from " << mySong->getFeaturing() << " to " << song.getFeaturing() << endl;
                }
                if (mySong->getFilepath().compare(song.getFilename())) {
                    songNeedsUpdating = true;
                    mySong->setFilepath(song.getFilename());
                    cout << "updating song " << mySong->getId() << " filepath from " << mySong->getFilepath() << " to " << song.getFilename() << endl;
                }
                if (mySong->getRating() != song.getRating()) {
                    songNeedsUpdating = true;
                    mySong->setRating(song.getRating());
                    cout << "updating song " << mySong->getId() << " rating from " << mySong->getRating() << " to " << song.getRating() << endl;
                }
                if (mySong->getRemix().compare(song.getRemix())) {
                    songNeedsUpdating = true;
                    mySong->setRemix(song.getRemix());
                    cout << "updating song " << mySong->getId() << " remix from " << mySong->getRemix() << " to " << song.getRemix() << endl;
                }
                if (mySong->getTitle().compare(song.getTitle())) {
                    songNeedsUpdating = true;
                    mySong->setTitle(song.getTitle());
                    cout << "updating song " << mySong->getId() << " title from " << mySong->getTitle() << " to " << song.getTitle() << endl;
                }
                if (mySong->getTrack().compare(song.getTrack())) {
                    songNeedsUpdating = true;
                    mySong->setTrack(song.getTrack());
                    cout << "updating song " << mySong->getId() << " track from " << mySong->getTrack() << " to " << song.getTrack() << endl;
                }
                if (mySong->getTrashed() != !song.getDisabled().compare("yes")) {
                    songNeedsUpdating = true;
                    mySong->setTrashed(!song.getDisabled().compare("yes"));
                    cout << "updating song " << mySong->getId() << " trashed from " << mySong->getTrashed() << " to " << song.getDisabled() << endl;
                }
                if (songNeedsUpdating)
                    mySong->update();
                if ((songNeedsUpdating || albumNeedsUpdating) != needsUpdating) {
                    cerr << "Why not more needing updates? Song " << mySong->getId() << " (" << songNeedsUpdating << "), Album " << album->getId() << " (" << albumNeedsUpdating << "), RE Song " << dbSong->getUniqueId() << " (" << needsUpdating << ")" << endl;
                }
            } else {
                cerr << "How do I have a RE Song " << dbSong->getUniqueId() << " yet no normal song?!" << endl;
                Song newSong(&song);
                newSong.save();
                delete newSong.getAlbum();
            }
            delete dbSong;
            delete mySong;
        } else {
            // saving a Song saves the RESong as well if it has no ID (ie. this case)
            Song mySong(&song);
            mySong.save();
            // TODO shouldn't have to delete albums for the songs to work.
            delete mySong.getAlbum();
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

}
