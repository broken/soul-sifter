//
//  Song.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Song__
#define __soul_sifter__Song__

#include <set>
#include <string>
#include <vector>

#include "Style.h"
#include "ResultSetIterator.h"
#include "RESong.h"
#include "Album.h"
#include "AlbumPart.h"

namespace sql {
    class ResultSet;
}

using namespace std;

namespace dogatech {
namespace soulsifter {

    class Song {
    public:
        Song();
        explicit Song(const Song& song);
        ~Song();
        void clear();

        static Song* findById(int id);
        static Song* findByFilepath(const string& filepath);
        static Song* findByRESongId(int reSongId);
        static ResultSetIterator<Song>* findAll();

        bool sync();
        int update();
        int save();

        explicit Song(RESong* song);

        static void findSongsByStyle(const Style& style, vector<Song*>** songsPtr);
        static RESong* createRESongFromSong(const Song& song);

        const string reAlbum() const;
        const string getDateAddedString() const;
        void setDateAddedToNow();

        const int getId() const;
        void setId(int id);
        const string& getArtist() const;
        void setArtist(const string& artist);
        const string& getTrack() const;
        void setTrack(const string& track);
        const string& getTitle() const;
        void setTitle(const string& title);
        const string& getRemixer() const;
        void setRemixer(const string& remixer);
        const string& getFeaturing() const;
        void setFeaturing(const string& featuring);
        const string& getFilepath() const;
        void setFilepath(const string& filepath);
        const int getRating() const;
        void setRating(int rating);
        const time_t getDateAdded() const;
        void setDateAdded(time_t dateAdded);
        const string& getBpm() const;
        void setBpm(const string& bpm);
        const set<string>& getTonicKeys() const;
        void setTonicKeys(const set<string>& tonicKeys);
        void addTonicKey(const string& tonicKey);
        void removeTonicKey(const string& tonicKey);
        const string& getComments() const;
        void setComments(const string& comments);
        const bool getTrashed() const;
        void setTrashed(bool trashed);
        const bool getLowQuality() const;
        void setLowQuality(bool lowQuality);
        const int getRESongId() const;
        void setRESongId(int reSongId);
        RESong* getRESong() const;
        void setRESong(const RESong& reSong);
        const int getAlbumId() const;
        void setAlbumId(int albumId);
        Album* getAlbum() const;
        void setAlbum(const Album& album);
        const int getAlbumPartId() const;
        void setAlbumPartId(int albumPartId);
        AlbumPart* getAlbumPart() const;
        void setAlbumPart(const AlbumPart& albumPart);
        const vector<Style*>& getStyles();
        void setStyles(const vector<Style*>& styles);
        void addStyleById(int styleId);
        void removeStyleById(int styleId);

        friend ResultSetIterator<Song>;

    private:
        int id;
        string artist;
        string track;
        string title;
        string remixer;
        string featuring;
        string filepath;
        int rating;
        time_t dateAdded;
        string bpm;
        set<string> tonicKeys;
        string comments;
        bool trashed;
        bool lowQuality;
        int reSongId;
        RESong* reSong;
        int albumId;
        Album* album;
        int albumPartId;
        AlbumPart* albumPart;
        vector<Style*> styles;
        vector<int> stylesIds;

        static void populateFields(const sql::ResultSet* rs, Song* song);
        static void populateStylesIds(Song* song);

        void operator=(const Song& song);
    };

}
}

#endif /* defined(__soul_sifter__Song__) */
