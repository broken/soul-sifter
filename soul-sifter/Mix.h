//
//  Mix.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Mix__
#define __soul_sifter__Mix__

#include <set>
#include <string>
#include <vector>

#include "ResultSetIterator.h"
#include "Song.h"

namespace sql {
    class ResultSet;
}

using namespace std;

namespace dogatech {
namespace soulsifter {

    class Mix {
    public:
        Mix();
        explicit Mix(const Mix& mix);
        ~Mix();
        void clear();

        static Mix* findById(int id);
        static Mix* findByOutSongIdAndInSongId(int outSongId, int inSongId);
        static ResultSetIterator<Mix>* findAll();

        bool sync();
        int update();
        int save();

        friend class RapidEvolutionDatabaseMixoutsMixoutHandler;

        static int mixoutCountForRESongId(int outSongId);

        const int getId() const;
        void setId(int id);
        const int getOutSongId() const;
        void setOutSongId(int outSongId);
        Song* getOutSong() const;
        void setOutSong(const Song& outSong);
        const int getInSongId() const;
        void setInSongId(int inSongId);
        Song* getInSong() const;
        void setInSong(const Song& inSong);
        const string& getBpmDiff() const;
        void setBpmDiff(const string& bpmDiff);
        const int getRank() const;
        void setRank(int rank);
        const string& getComments() const;
        void setComments(const string& comments);
        const bool getAddon() const;
        void setAddon(bool addon);

        friend ResultSetIterator<Mix>;

    private:
        int id;
        int outSongId;
        Song* outSong;
        int inSongId;
        Song* inSong;
        string bpmDiff;
        int rank;
        string comments;
        bool addon;

        static void populateFields(const sql::ResultSet* rs, Mix* mix);

        void operator=(const Mix& mix);
    };

}
}

#endif /* defined(__soul_sifter__Mix__) */
