//
//  MusicManager.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//
//  Core that manages possible tags for the music file. This is not multi-thread safe.

#import "MusicManager.h"

#include <stdio.h>
#include <id3/tag.h>
#include <id3/utils.h>
#include <id3/misc_support.h>
#include <id3/readers.h>

#import <stdlib.h>
#import "Song.h"

@implementation MusicManager

# pragma mark tagging

- (Song *)discoverSong:(NSURL *)musicFile {
    NSLog(@"discoverSong");
	NSLog(@"looking at '%@'", musicFile);
    Song *song = [[Song alloc] init];
    ID3_Tag tag([[musicFile path] cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    // TODO use an std::auto_ptr here to handle object cleanup automatically(void) ID3Tag_Link(tag, filename);
    ID3_Tag::Iterator* iter = tag.CreateIterator();
    const ID3_Frame* frame = NULL;
    while (NULL != (frame = iter->GetNext())) {
        const char* desc = frame->GetDescription();
        if (!desc) desc = "";
        NSLog(@" - frame: %s (%s): ", frame->GetTextID(), desc);
        ID3_FrameID eFrameID = frame->GetID();
        switch (eFrameID) {
            case ID3FID_LEADARTIST: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setArtist:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song artist]);
                break;
            }
            case ID3FID_ALBUM: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setAlbum:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song album]);
                break;
            }
            case ID3FID_TRACKNUM: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setTrackNum:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song trackNum]);
                break;
            }
            case ID3FID_TITLE: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setTitle:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song title]);
                break;
            }
            case ID3FID_MIXARTIST: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setRemix:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song remix]);
                break;
            }
            case ID3FID_BAND: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setFeaturing:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song featuring]);
                break;
            }
            // numeric string in the DDMM format
            case ID3FID_DATE: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                NSString *tmp = [song releaseDate];
                // reverse to MMDD format
                char day1 = sText[0];
                if (day1) {
                    char day2 = sText[1];
                    if (day2) {
                        char m1 = sText[2];
                        if (m1) {
                            char m2 = sText[3];
                            if (m2) {
                                sText[0] = m1;
                                sText[1] = m2;
                                sText[2] = day1;
                                sText[3] = day2;
                            }
                        }
                    }
                }
                if (tmp) {
                    [song setReleaseDate:[NSString stringWithFormat:@"%@%@",
                                          [song releaseDate], tmp]];
                    [tmp release];
                } else {
                    [song setReleaseDate:[NSString stringWithUTF8String:sText]];
                }
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song releaseDate]);
                break;
            }
            case ID3FID_YEAR: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                NSString *tmp = [song releaseDate];
                if (tmp) {
                    [song setReleaseDate:[NSString stringWithFormat:@"%@%@",
                                          tmp, [song releaseDate]]];
                    [tmp release];
                } else {
                    [song setReleaseDate:[NSString stringWithUTF8String:sText]];
                }
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song releaseDate]);
                break;
            }
            case ID3FID_PUBLISHER: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT);
                [song setLabel:[NSString stringWithUTF8String:sText]];
                delete [] sText;
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, [song label]);
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
            case ID3FID_ENCODERSETTINGS:
            case ID3FID_USERTEXT: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT),
                     *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION);
                NSLog(@" - frame %s (%s): %s", frame->GetTextID(), sDesc, sText);
                delete [] sText;
                delete [] sDesc;
                break;
            }
            case ID3FID_COMMENT:
            case ID3FID_UNSYNCEDLYRICS: {
                char *sText = ID3_GetString(frame, ID3FN_TEXT), 
                     *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION), 
                     *sLang = ID3_GetString(frame, ID3FN_LANGUAGE);
                NSLog(@" - frame %s (%s)[%s]: %s", frame->GetTextID(), sDesc, sLang, sText);
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
                NSLog(@" - frame %s (%s): %s", frame->GetTextID(), desc, sURL);
                delete [] sURL;
                break;
            }
            case ID3FID_WWWUSER: {
                char *sURL = ID3_GetString(frame, ID3FN_URL),
                     *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION);
                NSLog(@" - frame %s (%s): %s", frame->GetTextID(), sDesc, sURL);
                delete [] sURL;
                delete [] sDesc;
                break;
            }
            case ID3FID_INVOLVEDPEOPLE: {
                size_t nItems = frame->GetField(ID3FN_TEXT)->GetNumTextItems();
                NSString *ppl = @"";
                for (size_t nIndex = 0; nIndex < nItems; nIndex++) {
                    char *sPeople = ID3_GetString(frame, ID3FN_TEXT, nIndex);
                    if (nIndex + 1 < nItems) {
                        ppl = [NSString stringWithFormat:@"%@%s,", ppl, sPeople];
                    } else {
                        ppl = [NSString stringWithFormat:@"%@%s", ppl, sPeople];
                    }
                    delete [] sPeople;
                }
                NSLog(@" - frame %s (%s): %@", frame->GetTextID(), desc, ppl);
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
                NSLog(@" - frame %s (%s): %s, %lu: %s, %lu bytes", frame->GetTextID(), sDesc,
                      sFormat, nPicType, sMimeType, nDataSize);
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
                NSLog(@" - frame %s (%s): %s: %s, %lu bytes", frame->GetTextID(), sDesc,
                      sFileName, sMimeType, nDataSize);
                delete [] sMimeType;
                delete [] sDesc;
                delete [] sFileName;
                break;
            }
            case ID3FID_UNIQUEFILEID: {
                char *sOwner = ID3_GetString(frame, ID3FN_OWNER);
                size_t nDataSize = frame->GetField(ID3FN_DATA)->Size();
                NSLog(@" - frame %s (%s): %s, %lu bytes", frame->GetTextID(), desc, sOwner, nDataSize);
                delete [] sOwner;
                break;
            }
            case ID3FID_PLAYCOUNTER: {
                size_t nCounter = frame->GetField(ID3FN_COUNTER)->Get();
                NSLog(@" - frame %s (%s): %lu", frame->GetTextID(), desc, nCounter);
                break;
            }
            case ID3FID_POPULARIMETER: {
                char *sEmail = ID3_GetString(frame, ID3FN_EMAIL);
                size_t nCounter = frame->GetField(ID3FN_COUNTER)->Get(),
                       nRating = frame->GetField(ID3FN_RATING)->Get();
                NSLog(@" - frame %s (%s): %s, counter=%lu, rating=%lu", frame->GetTextID(), desc,
                      sEmail, nCounter, nRating);
                delete [] sEmail;
                break;
            }
            case ID3FID_CRYPTOREG:
            case ID3FID_GROUPINGREG: {
                char *sOwner = ID3_GetString(frame, ID3FN_OWNER);
                size_t nSymbol = frame->GetField(ID3FN_ID)->Get(),
                       nDataSize = frame->GetField(ID3FN_DATA)->Size();
                NSLog(@" - frame %s (%s): %s (%lu), %lu bytes", frame->GetTextID(), desc,
                      sOwner, nSymbol, nDataSize);
                break;
            }
            case ID3FID_SYNCEDLYRICS: {
                char *sDesc = ID3_GetString(frame, ID3FN_DESCRIPTION), 
                     *sLang = ID3_GetString(frame, ID3FN_LANGUAGE);
                size_t nTimestamp = frame->GetField(ID3FN_TIMESTAMPFORMAT)->Get(),
                       nRating = frame->GetField(ID3FN_CONTENTTYPE)->Get();
                const char* format = (2 == nTimestamp) ? "ms" : "frames";
                NSString *type;
                switch (nRating) {
                    case ID3CT_OTHER:    type = @"Other"; break;
                    case ID3CT_LYRICS:   type = @"Lyrics"; break;
                    case ID3CT_TEXTTRANSCRIPTION:     type = @"Text transcription"; break;
                    case ID3CT_MOVEMENT: type = @"Movement/part name"; break;
                    case ID3CT_EVENTS:   type = @"Events"; break;
                    case ID3CT_CHORD:    type = @"Chord"; break;
                    case ID3CT_TRIVIA:   type = @"Trivia/'pop up' information"; break;
                }
                NSLog(@" - frame %s (%s)[%s]: %@: %lu %s", frame->GetTextID(), sDesc,
                      sLang, type, nTimestamp, format);
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
                NSLog(@" - frame %s (%s): unimplemented", frame->GetTextID(), desc);
                break;
            }
            default: {
                NSLog(@" - frame %s: unknown", frame->GetTextID());
                break;
            }
        }
    }
    delete iter;
    
    return song;
}

@end
