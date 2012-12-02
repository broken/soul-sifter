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
        f << "<" << (*it)->getName() << ">" << (*it)->getValue() << "</" << (*it)->getName() << ">" << endl;
    }
    f << "</settings>" << endl;
    
    f << REXML::findByName("columns")->getXml() << endl;
    f << REXML::findByName("tables")->getXml() << endl;
    f << REXML::findByName("user")->getXml() << endl;
    
    const vector<const Style*>* styles;
    Style::findAll(&styles);
    f << "<styles dirty=\"no\" num_styles=\"" << styles->size() << "\">" << endl;
    for (vector<const Style*>::const_iterator it = styles->begin(); it != styles->end(); ++it) {
        f << "<style category_only=\"no\" child_ids=\"\" description=\"\" id=\"" << (*it)->getREId() << "\" name=\"" << (*it)->getREName() << "\" parent_ids\"\">" << endl;  // TODO child & parent ids
        // TODO includes
    }
    
    // TODO total songs
    f << "<songs check_unique_id=\"no\" max_unique_id=\"\">" << endl;
    RESong::RESongIterator* songs = RESong::findAll();
    RESong song;
    while (songs->next(&song)) {
        // TODO mixouts
        // TODO don't print on empty
        f << "<song num_excludes=\"0\" num_mixouts=\"0\">" << endl;
        f << "<unique_id>" << song.getUniqueId() << "</unique_id>" << endl;
        f << "<songid_winfo>" << song.getSongIdWInfo() << "</songid_winfo>" << endl;
        f << "<songid>" << song.getSongId() << "</songid>" << endl;
        f << "<shortid>" << song.getShortId() << "</shortid>" << endl;
        f << "<shortid_winfo>" << song.getShortIdWInfo() << "</shortid_winfo>" << endl;
        f << "<artist>" << song.getArtist() << "</artist>" << endl;
        f << "<album>" << song.getAlbum() << "</album>" << endl;
        f << "<track>" << song.getTrack() << "</track>" << endl;
        f << "<title>" << song.getTitle() << "</title>" << endl;
        f << "<remix>" << song.getRemix() << "</remix>" << endl;
        f << "<comments>" << song.getComments() << "</comments>" << endl;
        f << "<custom1>" << song.getFeaturing() << "</custom1>" << endl;
        f << "<custom2>" << song.getReleaseDate() << "</custom2>" << endl;
        f << "<custom3>" << song.getLabel() << "</custom3>" << endl;
        f << "<custom4>" << song.getCatalogId() << "</custom4>" << endl;
        f << "<time>" << song.getTime() << "</time>" << endl;
        f << "<time_signature>" << song.getTimeSignature() << "</time_signature>" << endl;
        f << "<filename>" << song.getFilename() << "</filename>" << endl;
        f << "<digital_only>" << song.getDigitalOnly() << "</digital_only>" << endl;
        f << "<disabled>" << song.getDisabled() << "</disabled>" << endl;
        f << "<compilation>" << song.getCompilation() << "</compilation>" << endl;
        f << "<key_start>" << song.getKeyStart() << "</key_start>" << endl;
        f << "<key_end>" << song.getKeyEnd() << "</key_end>" << endl;
        f << "<key_accuracy>" << song.getKeyAccuracy() << "</key_accuracy>" << endl;
        f << "<bpm_start>" << song.getBPMStart() << "</bpm_start>" << endl;
        f << "<bpm_end>" << song.getBPMEnd() << "</bpm_end>" << endl;
        f << "<bpm_accuracy>" << song.getBPMAccuracy() << "</bpm_accuracy>" << endl;
        f << "<beat_intensity>" << song.getBeatIntensity() << "</beat_intensity>" << endl;
        f << "<replay_gain>" << song.getReplayGain() << "</replay_gain>" << endl;
        f << "<num_plays>" << song.getNumPlays() << "</num_plays>" << endl;
        f << "<rating>" << song.getRating() << "</rating>" << endl;
        f << "<date_added>" << song.getDateAdded() << "</date_added>" << endl;
        f << "<styles_bitmask>" << song.getStylesBitmask() << "</styles_bitmask>" << endl;
        f << "</song>" << endl;
    }
    delete songs;
    f << "</songs>" << endl;
    
    // TODO mixouts
    
    f << "<excludes/>" << endl;
    
    // TODO artists?
    
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