//
//  MusicManager.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//
//  Core that manages possible tags for the music file. This is not multi-thread safe.

#include "MusicManager.h"

#include <algorithm>
#include <iostream>
#include <regex.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <taglib/apetag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/popularimeterframe.h>
#include <taglib/tbytevector.h>
#include <taglib/textidentificationframe.h>
#include <taglib/tpropertymap.h>
#include <taglib/tstring.h>
#include <taglib/tstringlist.h>

#include "BasicGenre.h"
//#import "Constants.h"
#include "Song.h"
#include "SoulSifterSettings.h"

using namespace boost;
using namespace std;

namespace soulsifter {

# pragma mark private helpers

namespace {
    
    const string getId3v2Text(TagLib::ID3v2::Tag* id3v2, const char* name) {
        TagLib::ID3v2::FrameList frameList = id3v2->frameListMap()[name];
        return frameList.isEmpty() ? "" : frameList.front()->toString().to8Bit();
    }

    void setId3v2Text(TagLib::ID3v2::Tag* id3v2, const char* name, const char* value) {
        id3v2->removeFrames(name);
        TagLib::ID3v2::TextIdentificationFrame *frame = new TagLib::ID3v2::TextIdentificationFrame(name, TagLib::String::Latin1);
        frame->setText(TagLib::String(value, TagLib::String::UTF8));
        id3v2->addFrame(frame);
    }
    
}

# pragma mark initialization

MusicManager::MusicManager() :
lastParsedSong(NULL),
lastSongFixed(NULL),
artistToGenre(1600),
lastDestinationPath() {
}

MusicManager::~MusicManager() {
    // TODO delete artistToGenre
}

# pragma mark tagging

void MusicManager::readTagsFromSong(Song* song) {
    if (!song->getAlbum()) {
        Album album;
        song->setAlbum(album);
    }
    
    if (boost::algorithm::ends_with(song->getFilepath(), ".mp3")) {
        TagLib::MPEG::File f(song->getFilepath().c_str());
        TagLib::ID3v1::Tag* id3v1 = f.ID3v1Tag();
        if (id3v1) {
            stringstream ss;
            if (id3v1->title() != TagLib::String::null) song->setTitle(id3v1->title().to8Bit());
            if (id3v1->artist() != TagLib::String::null) song->setArtist(id3v1->artist().to8Bit());
            if (id3v1->album() != TagLib::String::null) song->getAlbum()->setName(id3v1->album().to8Bit());
            if (id3v1->comment() != TagLib::String::null) song->setComments(id3v1->comment().to8Bit());
            //TODO if (id3v1->genre() != TagLib::String::null) song->setGenre(id3v1->genre().to8Bit());
            if (id3v1->year() != 0) song->getAlbum()->setReleaseDateYear(id3v1->year());
            if (id3v1->track() != 0) {
                ss.clear();
                ss << id3v1->track();
                song->setTrack(ss.str());
            }
        }
        TagLib::APE::Tag* ape = f.APETag();
        if (ape) {
            stringstream ss;
            /*if (ape->title() != TagLib::String::null) song->setTitle(ape->title().to8Bit());
            if (ape->artist() != TagLib::String::null) song->setArtist(ape->artist().to8Bit());
            if (ape->album() != TagLib::String::null) song->getAlbum()->setName(ape->album().to8Bit());
            if (ape->comment() != TagLib::String::null) song->setComments(ape->comment().to8Bit());
            //TODO if (ape->genre() != TagLib::String::null) song->setGenre(ape->genre().to8Bit());
            if (ape->year() != 0) song->getAlbum()->setReleaseDateYear(ape->year());
            if (ape->track() != 0) {
                ss.clear();
                ss << ape->track();
                song->setTrack(ss.str());
            }*/
        }
        TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag();
        if (id3v2) {
            stringstream ss;
            if (id3v2->artist() != TagLib::String::null) song->setArtist(id3v2->artist().to8Bit());
            song->setTrack(getId3v2Text(id3v2, "TRCK"));
            if (id3v2->title() != TagLib::String::null) song->setTitle(id3v2->title().to8Bit());
            song->setRemixer(getId3v2Text(id3v2, "TPE4"));
            song->getAlbum()->setArtist(getId3v2Text(id3v2, "TPE2"));
            if (id3v2->album() != TagLib::String::null) song->getAlbum()->setName(id3v2->album().to8Bit());
            song->getAlbum()->setLabel(getId3v2Text(id3v2, "TPUB"));
            song->getAlbum()->setCatalogId(getId3v2Text(id3v2, "TCID"));
            if (id3v2->year() != 0) song->getAlbum()->setReleaseDateYear(id3v2->year());
            //TODO if (id3v2->genre() != TagLib::String::null) song->setGenre(id3v2->genre().to8Bit());
            if (id3v2->comment() != TagLib::String::null) song->setComments(id3v2->comment().to8Bit());
            
            TagLib::ID3v2::FrameList frameList = id3v2->frameListMap()["POPM"];
            if (!frameList.isEmpty()) {
                TagLib::ID3v2::PopularimeterFrame *popm = dynamic_cast<TagLib::ID3v2::PopularimeterFrame*>(frameList.front());
                song->setRating(popm->rating());
            }
            
            // string in the DDMM format
            const string date = getId3v2Text(id3v2, "TDAT");
            char *tmp = new char[3];
            tmp[0] = date[0];
            tmp[1] = date[1];
            tmp[2] = '\0';
            if (tmp[0] != '0' || tmp[1] != '0')
                song->getAlbum()->setReleaseDateDay(atoi(tmp));
            tmp[0] = date[2];
            tmp[1] = date[3];
            song->getAlbum()->setReleaseDateMonth(atoi(tmp));
            delete [] tmp;
        }
    }
}

void MusicManager::writeTagsToSong(Song* song) {
    delete lastSongFixed;
    lastSongFixed = new Song(*song);
    
    if (boost::algorithm::ends_with(song->getFilepath(), ".mp3")) {
        TagLib::MPEG::File f(song->getFilepath().c_str());
        TagLib::ID3v1::Tag* v1 = f.ID3v1Tag();
        TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag(true);
        if (v1) {
            if (id3v2->title() == TagLib::String::null) id3v2->setTitle(v1->title());
            if (id3v2->artist() == TagLib::String::null) id3v2->setArtist(v1->artist());
            if (id3v2->album() == TagLib::String::null) id3v2->setAlbum(v1->album());
            if (id3v2->comment() == TagLib::String::null) id3v2->setComment(v1->comment());
            if (id3v2->genre() == TagLib::String::null) id3v2->setGenre(v1->genre());
            if (id3v2->year() == 0) id3v2->setYear(v1->year());
        }
        f.strip(TagLib::MPEG::File::ID3v1);
        id3v2->setArtist(song->getArtist());
        setId3v2Text(id3v2, "TRCK", song->getTrack().c_str());
        id3v2->setTitle(song->getTitle());
        setId3v2Text(id3v2, "TPE4", song->getRemixer().c_str());
        id3v2->setComment(song->getComments());
        setId3v2Text(id3v2, "TPE2", song->getAlbum()->getArtist().c_str());
        id3v2->setAlbum(song->getAlbum()->getName());
        setId3v2Text(id3v2, "TPUB", song->getAlbum()->getLabel().c_str());
        setId3v2Text(id3v2, "TCID", song->getAlbum()->getCatalogId().c_str());
        id3v2->setYear(song->getAlbum()->getReleaseDateYear());
        // set genre
        for (long i = song->getStyles().size(); i > 0; --i) {
            const char* style = song->getStyles().back()->getName().c_str();
            if (style[0] != '=' && style[0] != '_' && style[0] != '.') {
                setId3v2Text(id3v2, "TCON", style);
                break;
            }
        }
        // set rating
        {
            id3v2->removeFrames("POPM");
            TagLib::ID3v2::PopularimeterFrame *frame = new TagLib::ID3v2::PopularimeterFrame();
            frame->setRating(song->getRating());
            id3v2->addFrame(frame);
        }
        // set release day & month
        if (song->getAlbum()->getReleaseDateMonth() > 0) {
            ostringstream daymonth;
            if (song->getAlbum()->getReleaseDateDay() == 0) {
                daymonth << "00";
            } else if (song->getAlbum()->getReleaseDateDay() < 10) {
                daymonth << "0" << song->getAlbum()->getReleaseDateDay();
            } else {
                daymonth << song->getAlbum()->getReleaseDateDay();
            }
            if (song->getAlbum()->getReleaseDateMonth() < 10) {
                daymonth << "0" << song->getAlbum()->getReleaseDateMonth();
            } else {
                daymonth << song->getAlbum()->getReleaseDateMonth();
            }
            setId3v2Text(id3v2, "TDAT", daymonth.str().c_str());
        }
        bool result = f.save();
        if (!result) {
            cerr << "unable to save " << song->getFilepath() << endl;
        }
    }
}
    
# pragma mark monitor changes
    
    Song* MusicManager::updateSongWithChanges(const Song& song) {
        Song *updatedSong = new Song(song);
        updatedSong->setAlbum(*song.getAlbum());
        
        // compare with last
        if (lastParsedSong && lastSongFixed) {
            if (!song.getArtist().compare(lastParsedSong->getArtist())) {
                boost::regex featRegex(" [(]ft[.] .*");
                updatedSong->setArtist(boost::regex_replace(lastSongFixed->getArtist(), featRegex, ""));
            }
            if (song.getTrack().length() == 0) {
                // TODO increment track #
            }
            // we shouldn't auto set track title b/c it changes so much
            // nor should we auto update remixer
            if (!song.getAlbum()->getArtist().compare(lastParsedSong->getAlbum()->getArtist())) {
                updatedSong->getAlbum()->setArtist(lastSongFixed->getAlbum()->getArtist());
            }
            if (!song.getAlbum()->getName().compare(lastParsedSong->getAlbum()->getName())) {
                updatedSong->getAlbum()->setName(lastSongFixed->getAlbum()->getName());
            }
            updatedSong->getAlbum()->setMixed(lastSongFixed->getAlbum()->getMixed());
            if (!song.getAlbum()->getLabel().compare(lastParsedSong->getAlbum()->getLabel())) {
                updatedSong->getAlbum()->setLabel(lastSongFixed->getAlbum()->getLabel());
            }
            if (!song.getAlbum()->getCatalogId().compare(lastParsedSong->getAlbum()->getCatalogId())) {
                updatedSong->getAlbum()->setCatalogId(lastSongFixed->getAlbum()->getCatalogId());
            }
            if (song.getAlbum()->getReleaseDateYear() == lastParsedSong->getAlbum()->getReleaseDateYear()) {
                updatedSong->getAlbum()->setReleaseDateYear(lastSongFixed->getAlbum()->getReleaseDateYear());
            }
            if (song.getAlbum()->getReleaseDateMonth() == lastParsedSong->getAlbum()->getReleaseDateMonth()) {
                updatedSong->getAlbum()->setReleaseDateMonth(lastSongFixed->getAlbum()->getReleaseDateMonth());
            }
            if (song.getAlbum()->getReleaseDateDay() == lastParsedSong->getAlbum()->getReleaseDateDay()) {
                updatedSong->getAlbum()->setReleaseDateDay(lastSongFixed->getAlbum()->getReleaseDateDay());
            }
            if (song.getAlbum()->getBasicGenreId() == lastParsedSong->getAlbum()->getBasicGenreId()) {
                updatedSong->getAlbum()->setBasicGenreId(lastSongFixed->getAlbum()->getBasicGenreId());
            }
        }
        
        // strip featuring from the title and add it to the artist.
        boost::regex featRegex(" [(]?[Ff](eaturing|t[.]?|eat[.]?) (.*?)[)]?$");
        boost::smatch featMatch;
        if (boost::regex_search(song.getTitle(), featMatch, featRegex, boost::match_extra)) {
            updatedSong->setArtist(updatedSong->getArtist() + " (ft. " + featMatch[2] + ")");
            updatedSong->setTitle(boost::regex_replace(updatedSong->getTitle(), featRegex, ""));
        }
        // copy remixer
        boost::regex rmxrRegex("[(](.*) ([Rr]emix|[Rr]mx|[Mm]ix|[Rr]efix)[)]$");
        boost::smatch rmxrMatch;
        if (boost::regex_search(song.getTitle(), rmxrMatch, rmxrRegex, boost::match_extra) &&
            updatedSong->getRemixer().length() == 0) {
            updatedSong->setRemixer(rmxrMatch[1]);
        }
        
        delete lastParsedSong;
        lastParsedSong = new Song(song);
        lastParsedSong->setAlbum(*song.getAlbum());
        return updatedSong;
    }
    
    void MusicManager::setNewSongChanges(const Song& song) {
        delete lastSongFixed;
        lastSongFixed = new Song(song);
    }
    
    void MusicManager::updateLastSongAlbumArtWithImage(const string& img) {
        if (!lastSongFixed) return;
        
        // code taken from moveImage(img)
        stringstream destpath;
        boost::filesystem::path src(img);
        destpath << lastDestinationPath << "/" << src.filename().string();
        
        Album* album = lastSongFixed->getAlbum();
        album->setCoverFilepath(destpath.str());
        album->update();
    }
                
# pragma mark paths
 
string MusicManager::getCopyToPath() {
    filesystem::path dir(SoulSifterSettings::getInstance().getMusicPath());
    if (filesystem::exists(dir) && filesystem::is_directory(dir)) {
        return SoulSifterSettings::getInstance().getMusicPath();
    }
    filesystem::path staging(SoulSifterSettings::getInstance().getStagingPath());
    if (filesystem::exists(staging) && filesystem::is_directory(staging)) {
        return SoulSifterSettings::getInstance().getStagingPath();
    }
    return "";
}

bool MusicManager::moveSong(Song* song) {
    try {
        // create directory
        string dirpath;
        {
            ostringstream ssdirpath;
            ssdirpath << SoulSifterSettings::getInstance().getStagingPath() << "/" << song->getAlbum()->getBasicGenre()->getName() << "/" << song->getAlbum()->getArtist() << "/" << song->getAlbum()->getName();
            dirpath = ssdirpath.str();
        }
        transform(dirpath.begin(), dirpath.end(), dirpath.begin(), ::tolower);
        filesystem::path dir(dirpath);
        if (!filesystem::exists(dir)) {
            if (!filesystem::create_directories(dir)) {
                cerr << "Error occurred while trying to create directory " << dirpath << endl;
                return false;
            }
        } else if (!filesystem::is_directory(dir)) {
            cerr << "Cannot move file b/c destination is not a directory " << dirpath << endl;
            return false;
        }
    
        // move file to dest
        stringstream destpath;
        boost::filesystem::path src(song->getFilepath());
        lastDestinationPath = dirpath;
        destpath << lastDestinationPath << "/" << src.filename().string();
        boost::filesystem::path dest(destpath.str());
        boost::filesystem::rename(src, dest);
        
        // update song path
        song->setFilepath(destpath.str());
    
        return true;  //TODO better testing
    } catch (const filesystem::filesystem_error& ex) {
        cerr << ex.what() << '\n';
    }
    return false;
}

    bool MusicManager::moveImage(const string& img) {
        try {
            // move file to dest
            stringstream destpath;
            boost::filesystem::path src(img);
            destpath << lastDestinationPath << "/" << src.filename().string();
            boost::filesystem::path dest(destpath.str());
            boost::filesystem::rename(src, dest);
            
            return true;
        } catch (const filesystem::filesystem_error& ex) {
            cerr << ex.what() << '\n';
        }
        return false;
    }
    
/*
// TODO remove old directories from staging
- (void)populateStagingDirectory {
    NSLog(@"musicManager.populateStagingDirectory");
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;
    
    // verify paths exist
    NSString *path;
    if (![self getCopyToPath:&path]) {
        return;
    }
    
    // enumerate over path; releasing values with each iteration for better memory management
	NSDirectoryEnumerator *enumerator  = [fileManager enumeratorAtPath:path];
	NSString *file;
	while (file = [enumerator nextObject]) {
		NSDictionary *fileAttribs = [enumerator fileAttributes];
		
        // we process all directories that do not start with a period
		if ([fileAttribs objectForKey:NSFileType] == NSFileTypeDirectory) {
			if ([file characterAtIndex:0] == '.') {
				continue;
			}
            NSURL *path = [NSURL fileURLWithPathComponents:
                           [NSArray arrayWithObjects:
                            [userDefaults stringForKey:UDStagingPath], file , nil]];
            NSLog(@"creating directory: %@", path);
            if (![fileManager createDirectoryAtURL:path withIntermediateDirectories:YES attributes:nil error:&error]) {
                NSString *msg = [NSString stringWithFormat:@"Error occurred while trying to create directory: %@", error];
                NSAssert(NO, msg);
            }
		}
	}
}
*/
    void MusicManager::flushStagingDirectory() {
        try {
            filesystem::path musicPath(SoulSifterSettings::getInstance().getMusicPath());
            if (!filesystem::exists(musicPath) || !filesystem::is_directory(musicPath)) {
                cerr << "music path does not exist or is not a directory: " << musicPath.string() << endl;
                return;
            }
            filesystem::path stagingPath(SoulSifterSettings::getInstance().getStagingPath());
            if (!filesystem::exists(stagingPath) || !filesystem::is_directory(stagingPath)) {
                cerr << "staging path does not exist or is not a directory: " << stagingPath.string() << endl;
                return;
            }
            
            // enumerate over paths
            unsigned long relativePathPosition = stagingPath.string().length();
            filesystem::recursive_directory_iterator end; // default ctor yields past the end
            for (filesystem::recursive_directory_iterator it(stagingPath); it != end; ++it) {
                if (filesystem::is_directory(it->status())) {
                    // do nothing
                } else if (filesystem::is_regular_file(it->status())) {
                    if (it->path().filename().string()[0] == '.') {
                        continue;
                    }
                    // create directory if it doesn't exist
                    string subPath = it->path().parent_path().string().substr(relativePathPosition);
                    filesystem::path dir(musicPath.string() + subPath);
                    if (!filesystem::exists(dir)) {
                        if (!filesystem::create_directories(dir)) {
                            cerr << "Error occurred while trying to create directory " << dir.string() << endl;
                            continue;
                        }
                    } else if (!filesystem::is_directory(dir)) {
                        cerr << "Cannot move file b/c destination is not a directory " << dir.string() << endl;
                        continue;
                    }
                    // move file
                    stringstream destpath;
                    destpath << dir.string() << "/" << it->path().filename().string();
                    filesystem::path dest(destpath.str());
                    cerr << "Moving " << it->path().string() << " to " << dest.string() << endl;
                    filesystem::copy(it->path(), dest);
                    if (filesystem::exists(dest)) {
                        filesystem::path trash("/Users/rneale/.Trash/" + it->path().filename().string());
                        filesystem::rename(it->path(), trash);
                    }
                    
                    // update song path
                    Song *song = Song::findByFilepath(it->path().string());
                    if (song) {
                        song->setFilepath(dest.string());
                        song->update();
                        delete song;
                    } else {
                        Album *album = Album::findByCoverFilepath(it->path().string());
                        if (album) {
                            album->setCoverFilepath(dest.string());
                            album->update();
                            delete album;
                        }
                    }
                } else {
                    cerr << "wtf is this? " << it->path().string() << endl;
                }
            }
        } catch (const filesystem::filesystem_error& ex) {
            cerr << ex.what() << '\n';
        }
    }

# pragma mark db updates

void MusicManager::updateDatabaseBasicGenres() {
    // TODO the artists to genres
    try {
        filesystem::path path(getCopyToPath());
        if (!filesystem::exists(path)) {
            cerr << "Cannot update db basic genres because path does not exist: " << getCopyToPath() << endl;
            return;
        } else if (!filesystem::is_directory(path)) {
            cerr << "Cannot update db basic genres because path is not a directory: " << getCopyToPath() << endl;
            return;
        }
        
        filesystem::directory_iterator end; // default ctor yields past the end
        for (filesystem::directory_iterator it(path); it != end; ++it) {
            if (filesystem::is_directory(it->status())) {
                string filename = it->path().filename().string();
                const BasicGenre *genre = BasicGenre::findByName(filename);
                if (!genre) {
                    BasicGenre *basicGenre = new BasicGenre();
                    basicGenre->setName(filename);
                    basicGenre->save();
                    genre = BasicGenre::findByName(filename);
                }
                for (filesystem::directory_iterator jt(it->path()); jt != end; ++jt) {
                    string artist = jt->path().filename().string();
                    artistToGenre[artist] = genre;
                }
            }
        }
    } catch (const filesystem::filesystem_error& ex) {
        cerr << ex.what() << '\n';
    }
}
   
const BasicGenre* MusicManager::findBasicGenreForArtist(const string& artist) {
    return artistToGenre[artist];
}
                
 /*
# pragma mark paths accessors

- (NSArray *)basicGenres {
    NSLog(@"musicManager.basicGenreList");
    if (!basicGenres) {
        [self initializePathMembers];
    }
    return basicGenres;
}

@end*/
}
