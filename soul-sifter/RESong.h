//
//  RESong.h
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#ifndef __soul_sifter__RESong__
#define __soul_sifter__RESong__

#include <string>

using namespace std;

namespace sql {
    class ResultSet;
}

class RESong {
public:
    friend class RapidEvolutionDatabaseSongsSongHandler;
    
    class RESongIterator {
    public:
        explicit RESongIterator(sql::ResultSet* resultset);
        ~RESongIterator();
        
        bool next(RESong* song);
    private:
        sql::ResultSet* rs;
        
        RESongIterator();
    };
    
    RESong();
    ~RESong();
    
    static RESong* findByUniqueId(const int uniqueId);
    static RESong* findBySongId(const string& songId);
    static bool lookup(RESong *song);  // deprecated
    static RESongIterator* findAll();
    static const int maxREId();
    
    bool update();
    const RESong* save();
    
    void clear();  // deprecated
    
    const int getUniqueId() const;
    void setUniqueId(const int unique_id);
    const string& getSongIdWInfo() const;
    void setSongIdWInfo(const string& songid_winfo);
    const string& getSongId() const;
    void setSongId(const string& songid);
    const string& getShortId() const;
    void setShortId(const string& shortid);
    const string& getShortIdWInfo() const;
    void setShortIdWInfo(const string& shortid_winfo);
    const string& getArtist() const;
    void setArtist(const string& artist);
    const string& getAlbum() const;
    void setAlbum(const string& album);
    const string& getTrack() const;
    void setTrack(const string& track);
    const string& getTitle() const;
    void setTitle(const string& title);
    const string& getTime() const;
    void setTime(const string& time);
    const string& getTimeSignature() const;
    void setTimeSignature(const string& time_signature);
    const string& getFilename() const;
    void setFilename(const string& filename);
    const string& getDigitalOnly() const;
    void setDigitalOnly(const string& digital_only);
    const string& getCompilation() const;
    void setCompilation(const string& compilation);
    const string& getKeyStart() const;
    void setKeyStart(const string& key_start);
    const int getKeyAccuracy() const;
    void setKeyAccuracy(const int key_accuracy);
    const double getBPMStart() const;
    void setBPMStart(const double bpm_start);
    const int getBPMAccuracy() const;
    void setBPMAccuracy(const int bpm_accuracy);
    const int getRating() const;
    void setRating(const int rating);
    const string& getDateAdded() const;
    void setDateAdded(const string& date_added);
    const string& getCatalogId() const;
    void setCatalogId(const string& catalogId);
    const string& getLabel() const;
    void setLabel(const string& label);
    const string& getRemix() const;
    void setRemix(const string& remix);
    const int getNumPlays() const;
    void setNumPlays(const int num_plays);
    const string& getComments() const;
    void setComments(const string& comments);
    const string& getReleaseDate() const;
    void setReleaseDate(const string& release_date);
    const string& getFeaturing() const;
    void setFeaturing(const string& featuring);
    const string& getKeyEnd() const;
    void setKeyEnd(const string& key_end);
    const string& getDisabled() const;
    void setDisabled(const string& disabled);
    const double getBPMEnd() const;
    void setBPMEnd(const double bpm_end);
    const int getBeatIntensity() const;
    void setBeatIntensity(const int beat_intensity);
    const double getReplayGain() const;
    void setReplayGain(const double replay_gain);
    const string& getStylesBitmask() const;
    void setStylesBitmask(const string& styles_bitmask);
    
private:
    int unique_id;
    string songid_winfo;
    string songid;
    string shortid;
    string shortid_winfo;
    string artist;
    string album;
    string track;
    string title;
    string time;
    string time_signature;
    string filename;
    string digital_only;
    string compilation;
    string key_start;
    int key_accuracy;
    double bpm_start;
    int bpm_accuracy;
    int rating;
    string date_added;
    string catalog_id;  // custom4
    string label;  // custom3
    string remix;
    int num_plays;
    string comments;
    string release_date;  // custom2
    string featuring;  // custom1
    string key_end;
    string disabled;
    double bpm_end;
    int beat_intensity;
    double replay_gain;
    string styles_bitmask;
};

#endif /* defined(__soul_sifter__RESong__) */
