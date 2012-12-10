//
//  TagInfoController.mm
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "TagInfoController.h"

#include "Album.h"
#import "ArchiveUtil.h"
#include "BasicGenre.h"
#import "Constants.h"
#include "MusicManager.h"
#include "Song.h"


# pragma mark private method helpers

@interface TagInfoController()

- (void)loadNextFile;

@end


@implementation TagInfoController

# pragma mark initialization

- (id)initWithWindow:(NSWindow *)window {
    NSLog(@"tagInfoController.initWithWindow");
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc {
    NSLog(@"tagInfoController.dealloc");
    [filesToTrash release];
    [super dealloc];
}

- (void)windowDidLoad {
    NSLog(@"tagInfoController.windowDidLoad");
    [super windowDidLoad];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    
    filesToTrash = [[NSMutableArray alloc] init];
    
    const vector<const soulsifter::BasicGenre*>* genres;
    soulsifter::BasicGenre::findAll(&genres);
    NSMutableArray* genresArray = [[NSMutableArray alloc] init];
    for (vector<const soulsifter::BasicGenre*>::const_iterator it = genres->begin(); it != genres->end(); ++it) {
        [genresArray addObject:[NSString stringWithUTF8String:(*it)->getName().c_str()]];
    }
    [genreArrayController setContent:genresArray];
}

- (IBAction)showWindow:(id)sender {
    NSLog(@"tagInfoController.showWindow");
    [super showWindow:sender];
    
    // TODO alert if directories don't exist
    index = -1;
    [self loadNextFile];
}

# pragma mark actions

- (IBAction)processMusicFile:(id)sender {
    NSLog(@"tagInfoController.processMusicFile");
    
    // unable to move file if any of these are blank
    if ([genreComboBox stringValue] == nil || [[genreComboBox stringValue] length] <= 0 ||
        [artist stringValue] == nil || [[artist stringValue] length] <= 0 ||
        [album stringValue] == nil || [[album stringValue] length] <= 0) {
        NSBeep();
        return;
    }
    
    soulsifter::Song song;
    song.setAlbum(new soulsifter::Album());
    song.setFilepath([[[fileUrls objectAtIndex:index] path] UTF8String]);
    song.setArtist([[artist stringValue] UTF8String]);
    song.getAlbum()->setName([[album stringValue] UTF8String]);
    song.setTrack([[trackNum stringValue] UTF8String]);
    song.setTitle([[title stringValue] UTF8String]);
    song.setRemix([[remix stringValue] UTF8String]);
    song.setFeaturing([[featuring stringValue] UTF8String]);
    song.getAlbum()->setLabel([[label stringValue] UTF8String]);
    song.getAlbum()->setCatalogId([[catalogId stringValue] UTF8String]);
    song.getAlbum()->setReleaseDateYear([releaseDateYear intValue]);
    song.getAlbum()->setReleaseDateMonth([releaseDateMonth intValue]);
    song.getAlbum()->setReleaseDateDay([releaseDateDay intValue]);
    song.setRating([rating intValue]);
    song.getAlbum()->setBasicGenre(soulsifter::BasicGenre::findByName([[genreComboBox stringValue] UTF8String]));
    
    // update tag
    soulsifter::MusicManager::getInstance().writeTagsToSong(&song);
    
    // move file
    soulsifter::MusicManager::getInstance().moveSong(&song);
    
    // load next song
    [self loadNextFile];
}

- (void)loadNextFile {
    NSLog(@"tagInfoController.loadNextFile");
    ++index;
    
    // close window if no more files to process
    if ([fileUrls count] <= index) {
        NSLog(@"No more files to process; closing tag info window");
        // trash files if desired
        NSURL *fileToTrash;
        for (fileToTrash in filesToTrash) {
            NSLog(@"trashing file %@", fileToTrash);
            [[NSFileManager defaultManager] trashItemAtURL:fileToTrash resultingItemURL:nil error:nil];
        }
        [filesToTrash removeAllObjects];
        [self close];
        return;
    }
    
    // skip files starting with period
    NSURL *fileUrl = [fileUrls objectAtIndex:index];
    if ([[fileUrl lastPathComponent] characterAtIndex:0] == '.') {
        NSLog(@"skipping %@", fileUrl);
        [self loadNextFile];
        return;
    }
    
    // if file is directory, enumerate over it and add files 
    NSDictionary *fileAttribs = [[NSFileManager defaultManager] attributesOfItemAtPath:[fileUrl path]
                                                                                 error:nil];
    if ([fileAttribs objectForKey:NSFileType] == NSFileTypeDirectory) {
        NSDirectoryEnumerator *enumerator = [[NSFileManager defaultManager]
                                             enumeratorAtPath:[fileUrl path]];
        NSString *childFile;
        while (childFile = [enumerator nextObject]) {
            NSDictionary *childFileAttribs = [enumerator fileAttributes];
            // this enumerator recurses directories. so no need to add them.
            if ([childFileAttribs objectForKey:NSFileType] == NSFileTypeRegular) {
                [fileUrls addObject:[fileUrl URLByAppendingPathComponent:childFile]];
            }
        }
        [filesToTrash addObject:fileUrl];
        [self loadNextFile];
        return;
    }
    
    // straight move images to last directory
    // TODO we should make this smarter
    if ([[[fileUrl pathExtension] lowercaseString] isEqualToString:@"jpg"] ||
        [[[fileUrl pathExtension] lowercaseString] isEqualToString:@"jpeg"] ||
        [[[fileUrl pathExtension] lowercaseString] isEqualToString:@"gif"] ||
        [[[fileUrl pathExtension] lowercaseString] isEqualToString:@"png"]) {
        //TODO [musicManager moveImage:fileUrl];
        [self loadNextFile];
        return;
    }
    
    // unarchive zips & rars, adding extracted files
    if ([[NSPredicate predicateWithFormat:@"self matches[c] \".+\\.part\\d+\\.rar$\""] evaluateWithObject:[fileUrl lastPathComponent]]) {
        // TODO be smarter; now we rely on hitting part1 first
        if ([[fileUrl path] hasSuffix:@".part1.rar"]) {
            [fileUrls addObject:[ArchiveUtil unrarFile:fileUrl]];
        }
        [filesToTrash addObject:fileUrl];
        [self loadNextFile];
        return;
    } else if ([[fileUrl pathExtension] isEqualToString:@"rar"]) {
        [fileUrls addObject:[ArchiveUtil unrarFile:fileUrl]];
        [filesToTrash addObject:fileUrl];
        [self loadNextFile];
        return;
    } else if ([[fileUrl pathExtension] isEqualToString:@"zip"]) {
        [fileUrls addObject:[ArchiveUtil unzipFile:fileUrl]];
        [filesToTrash addObject:fileUrl];
        [self loadNextFile];
        return;
    }
    
    // at this point it should be a normal file that needs processing
    [filePath setStringValue:[fileUrl lastPathComponent]];
    soulsifter::Song *song = new soulsifter::Song();
    song->setFilepath([[fileUrl path] UTF8String]);
    soulsifter::MusicManager::getInstance().readTagsFromSong(song);
    if (!song->getArtist().empty()) [artist setStringValue:[NSString stringWithUTF8String:song->getArtist().c_str()]];
    if (!song->getAlbum()->getName().empty()) [album setStringValue:[NSString stringWithUTF8String:song->getAlbum()->getName().c_str()]];
    if (!song->getTrack().empty()) [trackNum setStringValue:[NSString stringWithUTF8String:song->getTrack().c_str()]];
    if (!song->getTitle().empty()) [title setStringValue:[NSString stringWithUTF8String:song->getTitle().c_str()]];
    if (!song->getRemix().empty()) [remix setStringValue:[NSString stringWithUTF8String:song->getRemix().c_str()]];
    if (!song->getFeaturing().empty()) [featuring setStringValue:[NSString stringWithUTF8String:song->getFeaturing().c_str()]];
    if (!song->getAlbum()->getLabel().empty()) [label setStringValue:[NSString stringWithUTF8String:song->getAlbum()->getLabel().c_str()]];
    if (!song->getAlbum()->getCatalogId().empty()) [catalogId setStringValue:[NSString stringWithUTF8String:song->getAlbum()->getCatalogId().c_str()]];
    if (song->getAlbum()->getReleaseDateYear()) [releaseDateYear setStringValue:[NSString stringWithFormat:@"%i",song->getAlbum()->getReleaseDateYear()]];
    if (song->getAlbum()->getReleaseDateMonth()) [releaseDateMonth setStringValue:[NSString stringWithFormat:@"%i",song->getAlbum()->getReleaseDateMonth()]];
    if (song->getAlbum()->getReleaseDateDay()) [releaseDateDay setStringValue:[NSString stringWithFormat:@"%i",song->getAlbum()->getReleaseDateDay()]];
    else [releaseDateDay setStringValue:@""];
    //if (!song->getAlbum()->getBasicGenre().empty()) [genreComboBox setStringValue:[NSString stringWithUTF8String:song->getAlubm()->getBasicGenre()];
    if (song->getRating()) [rating setIntValue:song->getRating()];
}

# pragma mark accessors

@synthesize fileUrls;
@synthesize filesToTrash;
@synthesize genreOptions;

@synthesize filePath;

@synthesize artist;
@synthesize album;
@synthesize trackNum;
@synthesize title;
@synthesize remix;
@synthesize featuring;
@synthesize label;
@synthesize catalogId;
@synthesize releaseDateYear;
@synthesize releaseDateMonth;
@synthesize releaseDateDay;
@synthesize rating;

@end
