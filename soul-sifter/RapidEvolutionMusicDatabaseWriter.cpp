//
//  RapidEvolutionMusicDatabaseWriter.cpp
//  soul-sifter
//
//  Created by Robby Neale on 12/1/12.
//
//

#include "RapidEvolutionMusicDatabaseWriter.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "REAlbumCover.h"
#include "RESetting.h"
#include "RESong.h"
#include "REXML.h"
#include "Style.h"

using namespace std;

# pragma mark initialization

RapidEvolutionMusicDatabaseWriter::RapidEvolutionMusicDatabaseWriter() :
processing(false) {
}

# pragma mark xml reader

void RapidEvolutionMusicDatabaseWriter::write() {
    cout << "RapidEvolutionMusicDatabaseWriter.write" << endl;
    
    ofstream f;
    f.open ("/Users/rneale/music_database.xml.out");
    
    f << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
    f << "<music_database version=\"1.04\">" << endl;
    f << "<config>" << endl;
    
    f << "<settings>" << endl;
    vector<const RESetting*> settings;
    RESetting::findAll(&settings);
    for (vector<const RESetting*>::iterator it = settings.begin(); it != settings.end(); ++it) {
        f << "<" << (*it)->getName();
        if ((*it)->getValue().length() > 0) {
            f << ">" << (*it)->getValue() << "</" << (*it)->getName() << ">" << endl;
        } else {
            f << "/>" << endl;
        }
    }
    f << "</settings>" << endl;
    
    // XML in these contains the newline at the end
    f << REXML::findByName("columns")->getXml();
    f << REXML::findByName("tables")->getXml();
    f << REXML::findByName("user")->getXml();
    
    const vector<Style*>* styles;
    const vector<Style*>* children;
    const vector<Style*>* parents;
    Style::findAll(&styles);
    f << "<styles dirty=\"no\" num_styles=\"" << styles->size() << "\">" << endl;
    for (vector<Style*>::const_iterator it = styles->begin(); it != styles->end(); ++it) {
        f << "<style category_only=\"no\" child_ids=\"";
        (*it)->getChildren(&children);
        bool first = true;
        for (vector<Style*>::const_iterator jt = children->begin(); jt != children->end(); ++jt) {
            if (!first) f << ",";
            f << (*jt)->getREId();
            first = false;
        }
        f << "\" description=\"\" id=\"" << (*it)->getREId() << "\" name=\"" << (*it)->getREName() << "\" parent_ids=\"";
        (*it)->getParents(&parents);
        first = true;
        for (vector<Style*>::const_iterator jt = parents->begin(); jt != parents->end(); ++jt) {
            if (!first) f << ",";
            f << (*jt)->getREId();
            first = false;
        }
        if (first) f << "-1";
        f << "\"/>" << endl;
        // TODO includes maybe?
    }
    f << "</styles>" << endl;
    
    f << "<songs check_unique_id=\"no\" max_unique_id=\"" << RESong::maxREId() + 1 << "\">" << endl;
    RESong::RESongIterator* songs = RESong::findAll();
    RESong song;
    while (songs->next(&song)) {
        // TODO mixouts
        f << "<song num_excludes=\"0\" num_mixouts=\"0\">" << endl;
        f << "<unique_id>" << song.getUniqueId() << "</unique_id>" << endl;
        f << "<songid_winfo>" << song.getSongIdWInfo() << "</songid_winfo>" << endl;
        f << "<songid>" << song.getSongId() << "</songid>" << endl;
        f << "<shortid>" << song.getShortId() << "</shortid>" << endl;
        f << "<shortid_winfo>" << song.getShortIdWInfo() << "</shortid_winfo>" << endl;
        if (song.getArtist().length() > 0)
            f << "<artist>" << song.getArtist() << "</artist>" << endl;
        if (song.getAlbum().length() > 0)
            f << "<album>" << song.getAlbum() << "</album>" << endl;
        if (song.getTrack().length() > 0)
            f << "<track>" << song.getTrack() << "</track>" << endl;
        if (song.getTitle().length() > 0)
            f << "<title>" << song.getTitle() << "</title>" << endl;
        if (song.getRemix().length() > 0)
            f << "<remix>" << song.getRemix() << "</remix>" << endl;
        if (song.getComments().length() > 0)
            f << "<comments>" << song.getComments() << "</comments>" << endl;
        if (song.getFeaturing().length() > 0)
            f << "<custom1>" << song.getFeaturing() << "</custom1>" << endl;
        if (song.getReleaseDate().length() > 0)
            f << "<custom2>" << song.getReleaseDate() << "</custom2>" << endl;
        if (song.getLabel().length() > 0)
            f << "<custom3>" << song.getLabel() << "</custom3>" << endl;
        if (song.getCatalogId().length() > 0)
            f << "<custom4>" << song.getCatalogId() << "</custom4>" << endl;
        if (song.getTime().length() > 0)
            f << "<time>" << song.getTime() << "</time>" << endl;
        if (song.getTimeSignature().length() > 0)
            f << "<time_signature>" << song.getTimeSignature() << "</time_signature>" << endl;
        if (song.getFilename().length() > 0)
            f << "<filename>" << song.getFilename() << "</filename>" << endl;
        if (song.getDigitalOnly().length() > 0)
            f << "<digital_only>" << song.getDigitalOnly() << "</digital_only>" << endl;
        if (song.getDisabled().length() > 0)
            f << "<disabled>" << song.getDisabled() << "</disabled>" << endl;
        if (song.getCompilation().length() > 0)
            f << "<compilation>" << song.getCompilation() << "</compilation>" << endl;
        if (song.getKeyStart().length() > 0)
            f << "<key_start>" << song.getKeyStart() << "</key_start>" << endl;
        if (song.getKeyEnd().length() > 0)
            f << "<key_end>" << song.getKeyEnd() << "</key_end>" << endl;
        if (song.getKeyAccuracy() > 0)
            f << "<key_accuracy>" << song.getKeyAccuracy() << "</key_accuracy>" << endl;
        if (song.getBPMStart() > 0) 
            f << "<bpm_start>" << song.getBPMStart() << "</bpm_start>" << endl;
        if (song.getBPMEnd() > 0)
            f << "<bpm_end>" << song.getBPMEnd() << "</bpm_end>" << endl;
        if (song.getBPMAccuracy() > 0)
            f << "<bpm_accuracy>" << song.getBPMAccuracy() << "</bpm_accuracy>" << endl;
        if (song.getBeatIntensity() > 0)
            f << "<beat_intensity>" << song.getBeatIntensity() << "</beat_intensity>" << endl;
        if (song.getReplayGain() > 0)
            f << "<replay_gain>" << song.getReplayGain() << "</replay_gain>" << endl;
        if (song.getNumPlays() > 0)
            f << "<num_plays>" << song.getNumPlays() << "</num_plays>" << endl;
        if (song.getRating() > 0)
            f << "<rating>" << song.getRating() << "</rating>" << endl;
        if (song.getDateAdded().length() > 0)
            f << "<date_added>" << song.getDateAdded() << "</date_added>" << endl;
        if (song.getStylesBitmask().length() > 0)
            f << "<styles_bitmask>" << song.getStylesBitmask() << "</styles_bitmask>" << endl;
        f << "</song>" << endl;
    }
    delete songs;
    f << "</songs>" << endl;
    
    // TODO mixouts
    f << "<mixouts/>" << endl;
    
    f << "<excludes/>" << endl;
    
    // TODO artists?
    f << "<artists/>" << endl;
    
    f << "<albumcovers>" << endl;
    REAlbumCover::REAlbumCoverIterator* covers = REAlbumCover::findAll();
    REAlbumCover ac;
    while (covers->next(&ac)) {
        f << "<albumcover id=\"" << ac.getREId() << "\" thumbnail=\"" << ac.getThumbnail() << "\">" << endl;
        f << "<image filename=\"" << ac.getThumbnail() << "\"/>" << endl;
        f << "</albumcover>" << endl;
    }
    delete covers;
    f << "</albumcovers>" << endl;
    
    f << "</music_database>" << endl;
}