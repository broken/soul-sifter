//
//  MusicManager.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//
//  Core that manages possible tags for the music file. This is not multi-thread safe.

#include "MusicManager.h"

#include <iostream>
#include <regex.h>
#include <string>
#include <sstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <id3/misc_support.h>
#include <id3/readers.h>
#include <id3/tag.h>
#include <id3/utils.h>
#include <id3/writers.h>

#include "BasicGenre.h"
//#import "Constants.h"
#include "Song.h"
#include "SoulSifterSettings.h"

using namespace boost;
using namespace std;

namespace soulsifter {

#define id3CatalogId "catalogId"

# pragma mark private helpers

namespace {
    
    ID3_Frame* updateTag(ID3_Tag* tag, ID3_FrameID frameId, const string& value) {
        ID3_Frame* frame = NULL;
        if (tag != NULL && value.length() > 0) {
            // remove previous tag
            while ((frame = tag->Find(frameId))) {
                frame = tag->RemoveFrame(frame);
                delete frame;
            }
            // add new tag
            if (tag->Find(frameId) == NULL) {
                frame = new ID3_Frame(frameId);
                if (frame && value.length()) {
                    frame->GetField(ID3FN_TEXT)->Set(value.c_str());
                    tag->AttachFrame(frame);
                }
            }
        }
        return frame;
    }
    
    ID3_Frame* updateTag(ID3_Tag* tag, ID3_FrameID frameId, int value) {
        ID3_Frame* frame = NULL;
        if (tag != NULL && value > 0) {
            // remove previous tag
            while ((frame = tag->Find(frameId))) {
                frame = tag->RemoveFrame(frame);
                delete frame;
            }
            // add new tag
            if (tag->Find(frameId) == NULL) {
                frame = new ID3_Frame(frameId);
                if (frame && value) {
                    frame->GetField(ID3FN_RATING)->Set(value);
                    tag->AttachFrame(frame);
                }
            }
        }
        return frame;
    }
    
    ID3_Frame* updateTag(ID3_Tag* tag, ID3_FrameID frameId, const string& value, const string& description) {
        ID3_Frame* frame = NULL;
        if (tag != NULL && value.length() > 0 && description.length() > 0) {
            // remove previous tag
            while ((frame = tag->Find(frameId, ID3FN_DESCRIPTION, description.c_str()))) {
                frame = tag->RemoveFrame(frame);
                delete frame;
            }
            // add new tag
            if (tag->Find(frameId, ID3FN_DESCRIPTION, description.c_str()) == NULL) {
                frame = new ID3_Frame(frameId);
                if (frame && value.length()) {
                    frame->GetField(ID3FN_TEXT)->Set(value.c_str());
                    frame->GetField(ID3FN_DESCRIPTION)->Set(description.c_str());
                    tag->AttachFrame(frame);
                }
            }
        }
        return frame;
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
    ID3_Tag tag(song->getFilepath().c_str());
    // TODO use an std::auto_ptr here to handle object cleanup automatically(void) ID3Tag_Link(tag, filename);
    ID3_Tag::Iterator* iter = tag.CreateIterator();
    const ID3_Frame* frame = NULL;
    while (NULL != (frame = iter->GetNext())) {
        const char* desc = frame->GetDescription();
        if (!desc) desc = "";
        ID3_FrameID eFrameID = frame->GetID();
        switch (eFrameID) {
            case ID3FID_LEADARTIST: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->setArtist(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getArtist() << endl;
                break;
            }
            case ID3FID_ALBUM: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->getAlbum()->setName(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getAlbum()->getName() << endl;
                break;
            }
            case ID3FID_TRACKNUM: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->setTrack(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getTrack() << endl;
                break;
            }
            case ID3FID_TITLE: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->setTitle(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getTitle() << endl;
                break;
            }
            case ID3FID_MIXARTIST: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->setRemix(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getRemix() << endl;
                break;
            }
            case ID3FID_BAND: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->setFeaturing(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getFeaturing() << endl;
                break;
            }
            // numeric string in the DDMM format
            case ID3FID_DATE: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                char *tmp = new char[3];
                tmp[0] = sText[0];
                tmp[1] = sText[1];
                tmp[2] = '\0';
                if (tmp[0] != '0' || tmp[1] != '0')
                    song->getAlbum()->setReleaseDateDay(atoi(tmp));
                tmp[0] = sText[2];
                tmp[1] = sText[3];
                song->getAlbum()->setReleaseDateMonth(atoi(tmp));
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << sText << endl;
                delete [] sText;
                delete [] tmp;
                break;
            }
            case ID3FID_YEAR: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->getAlbum()->setReleaseDateYear(atoi(sText));
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getAlbum()->getReleaseDateYear() << endl;
                break;
            }
            case ID3FID_PUBLISHER: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                song->getAlbum()->setLabel(sText);
                delete [] sText;
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << song->getAlbum()->getLabel() << endl;
                break;
            }
            case ID3FID_USERTEXT: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT),
                     *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION);
                string desc(sDesc);
                if (!desc.compare(id3CatalogId)) {
                    song->getAlbum()->setCatalogId(sText);
                }
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << sText << endl;
                break;
            }
            case ID3FID_POPULARIMETER: {
                char *sEmail = ID3_GetString(frame, ID3FN_EMAIL);
                size_t nCounter = frame->GetField(ID3FN_COUNTER)->Get(),
                nRating = frame->GetField(ID3FN_RATING)->Get();
                song->setRating((int)nRating);
                cout << "frame " << frame->GetTextID() << " (" << desc << "): " << sEmail << ", counter=" << nCounter << ", rating=" << nRating << endl;
                delete [] sEmail;
                break;
            }
            // the rest will just log messages
            case ID3FID_BPM:
            case ID3FID_COMPOSER:
            case ID3FID_CONTENTTYPE:
            case ID3FID_COPYRIGHT:
            case ID3FID_PLAYLISTDELAY:
            case ID3FID_ENCODEDBY:
            case ID3FID_LYRICIST:
            case ID3FID_FILETYPE:
            case ID3FID_TIME:
            case ID3FID_CONTENTGROUP:
            case ID3FID_SUBTITLE:
            case ID3FID_INITIALKEY:
            case ID3FID_LANGUAGE:
            case ID3FID_SONGLEN:
            case ID3FID_MEDIATYPE:
            case ID3FID_ORIGALBUM:
            case ID3FID_ORIGFILENAME:
            case ID3FID_ORIGLYRICIST:
            case ID3FID_ORIGARTIST:
            case ID3FID_ORIGYEAR:
            case ID3FID_FILEOWNER:
            case ID3FID_CONDUCTOR:
            case ID3FID_PARTINSET:
            case ID3FID_RECORDINGDATES:
            case ID3FID_NETRADIOSTATION:
            case ID3FID_NETRADIOOWNER:
            case ID3FID_SIZE:
            case ID3FID_ISRC:
            case ID3FID_ENCODERSETTINGS: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT),
                *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION);
                cout << "frame " << frame->GetTextID() << " (" << sDesc << ") : " << sText << endl;
                delete [] sText;
                delete [] sDesc;
                break;
            }
            case ID3FID_COMMENT:
            case ID3FID_UNSYNCEDLYRICS: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT), 
                     *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION), 
                *sLang = ID3_GetString(frame, ID3FN_LANGUAGE);
                cout << "frame " << frame->GetTextID() << " (" << sDesc << ")[" << sLang << "]: " << sText << endl;
                delete [] sText;
                delete [] sDesc;
                delete [] sLang;
                break;
            }
            case ID3FID_WWWAUDIOFILE:
            case ID3FID_WWWARTIST:
            case ID3FID_WWWAUDIOSOURCE:
            case ID3FID_WWWCOMMERCIALINFO:
            case ID3FID_WWWCOPYRIGHT:
            case ID3FID_WWWPUBLISHER:
            case ID3FID_WWWPAYMENT:
            case ID3FID_WWWRADIOPAGE: {
                char *sURL = ID3_GetString(frame, ID3FN_URL);
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << sURL << endl;
                delete [] sURL;
                break;
            }
            case ID3FID_WWWUSER: {
                char *sURL = ID3_GetString(frame, ID3FN_URL),
                *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION);
                cout << "frame " << frame->GetTextID() << " (" << sDesc << ") : " << sURL << endl;
                delete [] sURL;
                delete [] sDesc;
                break;
            }
            case ID3FID_INVOLVEDPEOPLE: {
                size_t nItems = frame->GetField(ID3FN_TEXT)->GetNumTextItems();
                stringstream ppl;
                for (size_t nIndex = 0; nIndex < nItems; nIndex++) {
                    char *sPeople = ID3_GetString(frame, ID3FN_TEXT, nIndex);
                    if (nIndex + 1 < nItems) {
                        ppl << sPeople << ",";
                    } else {
                        ppl << sPeople;
                    }
                    delete [] sPeople;
                }
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << ppl << endl;
                break;
            }
            case ID3FID_PICTURE: {
                char *sMimeType = ID3_GetString(frame, ID3FN_MIMETYPE),
                     *sDesc     = ID3_GetString(frame, ID3FN_DESCRIPTION),
                     *sFormat   = ID3_GetString(frame, ID3FN_IMAGEFORMAT);
                size_t nPicType   = frame->GetField(ID3FN_PICTURETYPE)->Get(),
                       nDataSize  = frame->GetField(ID3FN_DATA)->Size();
                std::cout << "(" << sDesc << ")[" << sFormat << ", "
                << nPicType << "]: " << sMimeType << ", " << nDataSize
                << " bytes" << std::endl;
                delete [] sMimeType;
                delete [] sDesc;
                delete [] sFormat;
                break;
            }
            case ID3FID_GENERALOBJECT: {
                char *sMimeType = ID3_GetString(frame, ID3FN_MIMETYPE), 
                     *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION), 
                     *sFileName = ID3_GetString(frame, ID3FN_FILENAME);
                size_t nDataSize = frame->GetField(ID3FN_DATA)->Size();
                cout << "frame " << frame->GetTextID() << " (" << sDesc << "): " << sFileName << ": " << sMimeType << ", " << nDataSize << " bytes" << endl;
                delete [] sMimeType;
                delete [] sDesc;
                delete [] sFileName;
                break;
            }
            case ID3FID_UNIQUEFILEID: {
                char *sOwner = ID3_GetString(frame, ID3FN_OWNER);
                size_t nDataSize = frame->GetField(ID3FN_DATA)->Size();
                cout << "frame " << frame->GetTextID() << " (" << desc << "): " << sOwner << ", " << nDataSize << " bytes" << endl;
                delete [] sOwner;
                break;
            }
            case ID3FID_PLAYCOUNTER: {
                size_t nCounter = frame->GetField(ID3FN_COUNTER)->Get();
                cout << "frame " << frame->GetTextID() << " (" << desc << ") : " << nCounter << endl;
                break;
            }
            case ID3FID_CRYPTOREG:
            case ID3FID_GROUPINGREG: {
                char *sOwner = ID3_GetString(frame, ID3FN_OWNER);
                size_t nSymbol = frame->GetField(ID3FN_ID)->Get(),
                        nDataSize = frame->GetField(ID3FN_DATA)->Size();
                cout << "frame " << frame->GetTextID() << " (" << desc << "): " << sOwner << " (" << nSymbol << ") , " << nDataSize << " bytes" << endl;
                break;
            }
            case ID3FID_SYNCEDLYRICS: {
                char *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION), 
                     *sLang = ID3_GetString(frame, ID3FN_LANGUAGE);
                size_t nTimestamp = frame->GetField(ID3FN_TIMESTAMPFORMAT)->Get(),
                       nRating = frame->GetField(ID3FN_CONTENTTYPE)->Get();
                const char* format = (2 == nTimestamp) ? "ms" : "frames";
                string type;
                switch (nRating) {
                    case ID3CT_OTHER:    type = "Other"; break;
                    case ID3CT_LYRICS:   type = "Lyrics"; break;
                    case ID3CT_TEXTTRANSCRIPTION:     type = "Text transcription"; break;
                    case ID3CT_MOVEMENT: type = "Movement/part name"; break;
                    case ID3CT_EVENTS:   type = "Events"; break;
                    case ID3CT_CHORD:    type = "Chord"; break;
                    case ID3CT_TRIVIA:   type = "Trivia/'pop up' information"; break;
                }
                cout << "frame " << frame->GetTextID() << " (" << sDesc << ")[" << sLang << "]: " << type << ": " << nTimestamp << " " << format << endl;
                ID3_Field* fld = frame->GetField(ID3FN_DATA);
                if (fld) {
                    // skip reading this
                    /*ID3_MemoryReader mr(fld->GetRawBinary(), fld->BinSize());
                    while (!mr.atEnd()) {
                        std::cout << io::readString(mr).c_str();
                        std::cout << " [" << io::readBENumber(mr, sizeof(uint32)) << " " 
                                  << format << "] ";
                    }*/
                }
                delete [] sDesc;
                delete [] sLang;
                break;
            }
            case ID3FID_AUDIOCRYPTO:
            case ID3FID_EQUALIZATION:
            case ID3FID_EVENTTIMING:
            case ID3FID_CDID:
            case ID3FID_MPEGLOOKUP:
            case ID3FID_OWNERSHIP:
            case ID3FID_PRIVATE:
            case ID3FID_POSITIONSYNC:
            case ID3FID_BUFFERSIZE:
            case ID3FID_VOLUMEADJ:
            case ID3FID_REVERB:
            case ID3FID_SYNCEDTEMPO:
            case ID3FID_METACRYPTO: {
                cout << "frame " << frame->GetTextID() << " (" << desc << "): unimplemented" << endl;
                break;
            }
            default: {
                cout << "frame " << frame->GetTextID() << ": unknown" << endl;
                break;
            }
        }
    }
    delete iter;
    
    /* TODO split remix from title
    if (song->getTitle()) {
        regex rgx("\\((.* ((remix)|(rmx)|(mix)|(refix)|(edit))\\)$");
        smatch groups;
        if (regex_search(song->getTitle(), groups, rgx)) {
        NSTextCheckingResult *match = nil;
        if ((match = [regex firstMatchInString:[song title] options:0 range:NSMakeRange(0, [[song title] length])])) {
            if (![song remix] || [[song remix] length] == 0) {
                [song setRemix:[[song title] substringWithRange:[match rangeAtIndex:1]]];
            }
            [song setTitle:[regex stringByReplacingMatchesInString:[song title]
                                                           options:0
                                                             range:NSMakeRange(0, [[song title] length])
                                                      withTemplate:@""]];
        }
    }
    // split featuring from artist
    if ([song artist]) {
        NSError *error = nil;
        NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@" \\(?((ft)|(featuring)|(feat))\\.? (.*)\\)?$"
                                                                               options:NSRegularExpressionCaseInsensitive
                                                                                 error:&error];
        NSTextCheckingResult *match = nil;
        if ((match = [regex firstMatchInString:[song artist] options:0 range:NSMakeRange(0, [[song artist] length])])) {
            [song setFeaturing:[[song artist] substringWithRange:[match rangeAtIndex:5]]];
            [song setArtist:[regex stringByReplacingMatchesInString:[song artist]
                                                            options:0
                                                              range:NSMakeRange(0, [[song artist] length])
                                                       withTemplate:@""]];
        }
    }*/
    
    Song *songBeforeFixing = new Song(*song);
    
    // compare with last
    if (lastParsedSong && lastSongFixed) {
        if (song->getArtist().length() == 0 || !song->getArtist().compare(lastParsedSong->getArtist())) {
            song->setArtist(lastSongFixed->getArtist());
        }
        if (song->getAlbum()->getName().length() == 0 || !song->getAlbum()->getName().compare(lastParsedSong->getAlbum()->getName())) {
            song->getAlbum()->setName(lastSongFixed->getAlbum()->getName());
        }
        if (song->getTrack().length() == 0) {
            // TODO increment track #
        }
        // we shouldn't auto set track title b/c it changes so much
        // we shouldn't auto set remix title b/c it changes so much
        // we shouldn't auto set featuring title b/c it changes so much
        if (song->getAlbum()->getLabel().length() == 0 || !song->getAlbum()->getLabel().compare(lastParsedSong->getAlbum()->getLabel())) {
            song->getAlbum()->setLabel(lastSongFixed->getAlbum()->getLabel());
        }
        if (song->getAlbum()->getCatalogId().length() == 0 || !song->getAlbum()->getCatalogId().compare(lastParsedSong->getAlbum()->getCatalogId())) {
            song->getAlbum()->setCatalogId(lastSongFixed->getAlbum()->getCatalogId());
        }
        if (song->getAlbum()->getReleaseDateYear() == 0 || song->getAlbum()->getReleaseDateYear() == lastParsedSong->getAlbum()->getReleaseDateYear()) {
            song->getAlbum()->setReleaseDateYear(lastSongFixed->getAlbum()->getReleaseDateYear());
        }
        if (song->getAlbum()->getReleaseDateMonth() == 0 || song->getAlbum()->getReleaseDateMonth() == lastParsedSong->getAlbum()->getReleaseDateMonth()) {
            song->getAlbum()->setReleaseDateMonth(lastSongFixed->getAlbum()->getReleaseDateMonth());
        }
        if (song->getAlbum()->getReleaseDateDay() == 0 || song->getAlbum()->getReleaseDateDay() == lastParsedSong->getAlbum()->getReleaseDateDay()) {
            song->getAlbum()->setReleaseDateDay(lastSongFixed->getAlbum()->getReleaseDateDay());
        }
        if (song->getAlbum()->getBasicGenreId() == 0 || song->getAlbum()->getBasicGenreId() == lastParsedSong->getAlbum()->getBasicGenreId()) {
            song->getAlbum()->setBasicGenreId(lastSongFixed->getAlbum()->getBasicGenreId());
        }
    }

    delete lastParsedSong;
    lastParsedSong = new Song(*songBeforeFixing);
}

void MusicManager::writeTagsToSong(Song* song) {
    delete lastSongFixed;
    lastSongFixed = song;
    
    ID3_Tag tag(song->getFilepath().c_str());
    updateTag(&tag, ID3FID_LEADARTIST, song->getArtist());
    updateTag(&tag, ID3FID_ALBUM, song->getAlbum()->getName());
    updateTag(&tag, ID3FID_TRACKNUM, song->getTrack());
    updateTag(&tag, ID3FID_TITLE, song->getTitle());
    updateTag(&tag, ID3FID_MIXARTIST, song->getRemix());
    updateTag(&tag, ID3FID_BAND, song->getFeaturing());
    updateTag(&tag, ID3FID_PUBLISHER, song->getAlbum()->getLabel());
    updateTag(&tag, ID3FID_USERTEXT, song->getAlbum()->getCatalogId(), id3CatalogId);
    if (song->getRating() > 0) {
        updateTag(&tag, ID3FID_POPULARIMETER, song->getRating());
    }
    if (song->getAlbum()->getReleaseDateYear() > 0) {
        ostringstream year;
        year << song->getAlbum()->getReleaseDateYear();
        updateTag(&tag, ID3FID_YEAR, year.str());
    }
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
        updateTag(&tag, ID3FID_DATE, daymonth.str());
    }
    tag.Update();
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
        ostringstream dirpath;
        dirpath << getCopyToPath() << "/" << song->getAlbum()->getBasicGenre()->getName() << "/" << song->getArtist() << "/" << song->getAlbum()->getName();
        filesystem::path dir(dirpath.str());
        if (!filesystem::exists(dir)) {
            if (!filesystem::create_directories(dir)) {
                cerr << "Error occurred while trying to create directory " << dirpath.str() << endl;
                return false;
            }
        } else if (!filesystem::is_directory(dir)) {
            cerr << "Cannot move file b/c destination is not a directory " << dirpath.str() << endl;
            return false;
        }
    
        // move file to dest
        stringstream destpath;
        boost::filesystem::path src(song->getFilepath());
        lastDestinationPath = dirpath.str();
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

- (void)flushStagingDirectory {
    NSLog(@"musicManager.flushStagingDirectory");
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;
    BOOL isDir;
    NSURL *stagingUrl = [[NSURL fileURLWithPath:[userDefaults stringForKey:UDStagingPath]] standardizedURL];
    NSURL *musicUrl = [[NSURL fileURLWithPath:[userDefaults stringForKey:UDMusicPath]] standardizedURL];
    
    if (![fileManager fileExistsAtPath:[musicUrl path] isDirectory:&isDir]
        || !isDir) {
        NSLog(@"Music path does not exist");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging directory failed"];
        [alert setInformativeText:@"Music path does not exist"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    if (![fileManager fileExistsAtPath:[stagingUrl path] isDirectory:&isDir]
        || !isDir) {
        NSLog(@"Staging path does not exist");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging directory failed"];
        [alert setInformativeText:@"Staging path does not exist"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    
    // enumerate over paths
    NSDirectoryEnumerator *enumerator = [fileManager enumeratorAtPath:[stagingUrl path]];
    NSString *file;
    while (file = [enumerator nextObject]) {
        file = [file stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		NSDictionary *fileAttribs = [enumerator fileAttributes];
        if ([fileAttribs objectForKey:NSFileType] == NSFileTypeRegular) {
            NSURL *fileUrl = [NSURL URLWithString:file relativeToURL:stagingUrl];
            if ([[fileUrl lastPathComponent] characterAtIndex:0] == '.') {
				continue;
			}
            NSURL *dest = [NSURL URLWithString:file relativeToURL:musicUrl];
            // create directory if it doesn't exist
            if (![fileManager createDirectoryAtURL:[dest URLByDeletingLastPathComponent]
                       withIntermediateDirectories:YES
                                        attributes:nil
                                             error:&error]) {
                NSString *msg = [NSString stringWithFormat:@"Error occurred while trying to create directory: %@", error];
                NSAssert(NO, msg);
            }
            // move file
            NSLog(@"moving '%@' to '%@'", fileUrl, dest);
            if (![fileManager moveItemAtURL:fileUrl toURL:dest error:&error]) {
                NSString *msg = [NSString stringWithFormat:@"Unable to move %@", file];
                NSAssert(NO, msg);
            }
        }
    }
}
*/
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
