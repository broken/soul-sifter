//
//  TagInfoController.mm
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "TagInfoController.h"

#include "Album.h"
#include "AlbumPart.h"
#import "ArchiveUtil.h"
#include "BasicGenre.h"
#import "Constants.h"
#include "MusicManager.h"
#import "NSOutlineView+DTSelection.h"
#include "RESong.h"
#include "Song.h"
#include "Style.h"
#import "StyleTreeItem.h"


# pragma mark private method helpers

@interface TagInfoController()

- (void)preprocessAllFiles:(NSArray *)files;
- (void)loadCover;
- (void)loadNextSong;
- (void)setFieldsAndUpdate:(BOOL)update;
- (bool)processSong;

@end


@implementation TagInfoController

# pragma mark initialization

- (id)initWithWindow:(NSWindow *)window {
    NSLog(@"tagInfoController.initWithWindow");
    self = [super initWithWindow:window];
    if (self) {
      // Initialization code here.
      filesToTrash = [[NSMutableArray alloc] init];
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
  
    const vector<const dogatech::soulsifter::BasicGenre*>* genres;
    dogatech::soulsifter::BasicGenre::findAll(&genres);
    NSMutableArray* genresArray = [[NSMutableArray alloc] init];
    for (vector<const dogatech::soulsifter::BasicGenre*>::const_iterator it = genres->begin(); it != genres->end(); ++it) {
        [genresArray addObject:[NSString stringWithUTF8String:(*it)->getName().c_str()]];
    }
    [genreArrayController setContent:genresArray];
}

- (IBAction)showWindow:(id)sender {
  NSLog(@"tagInfoController.showWindow");
  [super showWindow:sender];
    
  // TODO alert if directories don't exist
  delete filesToAdd;
  filesToAdd = new dogatech::soulsifter::FilesToAdd();
  hasMovedFile = false;
  [self preprocessAllFiles:fileUrls];
  [self loadCover];
  [fileUrls removeAllObjects];
  [self loadNextSong];
}


- (void)showWindow:(id)sender withSong:(dogatech::soulsifter::Song *)initialSong {
  NSLog(@"tagInfoController.showWindow withSong");
  [super showWindow:sender];
  
  // TODO alert if song not found
  delete filesToAdd;
  filesToAdd = new dogatech::soulsifter::FilesToAdd();
  filesToAdd->addSong(initialSong);
  [self loadCover];
  hasMovedFile = false;
  [fileUrls removeAllObjects];
  [self loadNextSong];
}

# pragma mark actions

- (void)preprocessAllFiles:(NSArray *)files {
  NSLog(@"tagInfoController.preprocessAllFiles");
  
  // TODO So I'd like to do this all in the FilesToAdd class, and should slowly move this over, but
  // I don't want to rewrite a lot of code, so I'll leverage this until porting the code over
  // to c++.
  for (NSURL *fileUrl in files) {
    // skip files starting with period
    if ([[fileUrl lastPathComponent] characterAtIndex:0] == '.') {
      NSLog(@"skipping %@", fileUrl);
      continue;
    }
    
    // if file is directory, enumerate over it and add files
    NSDictionary *fileAttribs =
    [[NSFileManager defaultManager] attributesOfItemAtPath:[fileUrl path] error:nil];
    if ([fileAttribs objectForKey:NSFileType] == NSFileTypeDirectory) {
      NSDirectoryEnumerator *enumerator = [[NSFileManager defaultManager] enumeratorAtPath:[fileUrl path]];
      NSString *childFile;
      NSMutableArray *childFileUrls = [[NSMutableArray alloc] init];
      while (childFile = [enumerator nextObject]) {
        NSDictionary *childFileAttribs = [enumerator fileAttributes];
        // this enumerator recurses directories. so no need to add them.
        if ([childFileAttribs objectForKey:NSFileType] == NSFileTypeRegular) {
          [childFileUrls addObject:[fileUrl URLByAppendingPathComponent:childFile]];
        }
      }
      // TODO fix issue where any files skipped in this directory will be deleted
      [filesToTrash addObject:fileUrl];
      [self preprocessAllFiles:childFileUrls];
      [childFileUrls release];
      continue;
    }
    
    // unarchive zips & rars, adding extracted files
    if ([[NSPredicate predicateWithFormat:@"self matches[c] \".+\\.part\\d+\\.rar$\""] evaluateWithObject:[fileUrl lastPathComponent]]) {
      if ([[fileUrl path] hasSuffix:@".part1.rar"]) {
        [self preprocessAllFiles:[NSArray arrayWithObject:[ArchiveUtil unrarFile:fileUrl]]];
      }
      [filesToTrash addObject:fileUrl];
      continue;
    } else if ([[fileUrl pathExtension] isEqualToString:@"rar"]) {
      [self preprocessAllFiles:[NSArray arrayWithObject:[ArchiveUtil unrarFile:fileUrl]]];
      [filesToTrash addObject:fileUrl];
      continue;
    } else if ([[fileUrl pathExtension] isEqualToString:@"zip"]) {
      [self preprocessAllFiles:[NSArray arrayWithObject:[ArchiveUtil unzipFile:fileUrl]]];
      [filesToTrash addObject:fileUrl];
      continue;
    }
    
    // let FilesToAdd do the rest
    filesToAdd->addFile([[fileUrl path] UTF8String]);
  }
}

- (void)loadCover {
  NSLog(@"tagInfoController.loadCover");
  if (filesToAdd->coverPath() == nil ||
      ![[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithUTF8String:filesToAdd->coverPath()->c_str()]]) {
    return;
  }
  NSImage* img = [[NSImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:filesToAdd->coverPath()->c_str()]];
  [img autorelease];
  [imageView setImage:img];
}

- (IBAction)switchCover:(id)sender {
  NSLog(@"tagInfoController.switchCover");
  filesToAdd->switchCover();
  [self loadCover];
}

- (void)loadNextSong {
  NSLog(@"tagInfoController.loadNextSong");
  
  if (filesToAdd->pullSong(&song)) {
    [self setFieldsAndUpdate:YES];
    return;
  }
  
  std::string *path;
  if (filesToAdd->pullFile(&path)) {
    // TODO only move image if a song has been moved or a song has not been skipped
    if (hasMovedFile) {
      // TODO move to last parent (no subalbums)
      // straight move image to last directory
      dogatech::soulsifter::MusicManager::getInstance().moveImage(*path);
      // TODO should this really happen here?
      // update album with cover art
      if (filesToAdd->coverPath() && !strcasecmp(path->c_str(), filesToAdd->coverPath()->c_str())) {
        dogatech::soulsifter::MusicManager::getInstance().updateLastSongAlbumArtWithImage(*path);
      }
    }
    delete path;
    [self loadNextSong];
  }
  
  // close window if no more files to process
  NSLog(@"No more files to process; closing tag info window");
  // trash files if desired
  NSURL *fileToTrash;
  for (fileToTrash in filesToTrash) {
    NSLog(@"trashing file %@", fileToTrash);
    [[NSFileManager defaultManager] trashItemAtURL:fileToTrash resultingItemURL:nil error:nil];
  }
  [filesToTrash removeAllObjects];
  [self close];
}

- (bool)processSong {
    // unable to move file if any of these are blank
    if ([genreComboBox stringValue] == nil || [[genreComboBox stringValue] length] <= 0 ||
        [artist stringValue] == nil || [[artist stringValue] length] <= 0 ||
        [album stringValue] == nil || [[album stringValue] length] <= 0) {
      NSBeep();
      return false;
    }
  
  dogatech::soulsifter::Album *songAlbum;
  if (song->getAlbum()) {
    // we make a copy of the album because we will end up deleting the original album and this one
    songAlbum = new dogatech::soulsifter::Album(*song->getAlbum());
  } else {
    songAlbum = new dogatech::soulsifter::Album();
  }
    song->setArtist([[artist stringValue] UTF8String]);
    song->setTrack([[trackNum stringValue] UTF8String]);
    song->setTitle([[title stringValue] UTF8String]);
    song->setRemixer([[remixer stringValue] UTF8String]);
    song->setComments([[comments stringValue] UTF8String]);
    song->setRating([rating intValue]);
    songAlbum->setArtist([[albumArtist stringValue] UTF8String]);
    songAlbum->setName([[album stringValue] UTF8String]);
    songAlbum->setLabel([[label stringValue] UTF8String]);
    songAlbum->setCatalogId([[catalogId stringValue] UTF8String]);
    songAlbum->setMixed([mixed state] == NSOnState);
    songAlbum->setReleaseDateYear([releaseDateYear intValue]);
    songAlbum->setReleaseDateMonth([releaseDateMonth intValue]);
    songAlbum->setReleaseDateDay([releaseDateDay intValue]);
    songAlbum->setBasicGenre(*dogatech::soulsifter::BasicGenre::findByName([[genreComboBox stringValue] UTF8String]));
    song->setAlbum(*songAlbum);
    NSIndexSet *styleIndexes = [styles selectedRowIndexes];
    for (NSUInteger idx = [styleIndexes firstIndex]; idx != NSNotFound; idx = [styleIndexes indexGreaterThanIndex:idx]) {
        StyleTreeItem *item = [styles itemAtRow:idx];
        dogatech::soulsifter::Style *style = [item style];
        song->addStyleById(style->getId());
    }
    if (!song->getRESongId()) {
        song->setRESong(*dogatech::soulsifter::Song::createRESongFromSong(*song));
    }
    
    // album part update
    if ([[albumPartOfSet stringValue] length] > 0 || [[albumPartName stringValue] length] > 0) {
        dogatech::soulsifter::AlbumPart *albumPart = song->getAlbumPart();
        if (!albumPart) {
            albumPart = new dogatech::soulsifter::AlbumPart();
        }
        albumPart->setAlbum(*songAlbum);
        albumPart->setName([[albumPartName stringValue] UTF8String]);
        albumPart->setPos([[albumPartOfSet stringValue] UTF8String]);
        song->setAlbumPart(*albumPart);
        delete albumPart;
    } else {
        song->setAlbumPartId(0);
    }
    
    // update tag
    dogatech::soulsifter::MusicManager::getInstance().writeTagsToSong(song);
    
    // move file
    dogatech::soulsifter::MusicManager::getInstance().moveSong(song);
    hasMovedFile = true;
    
    // save song
    if (!song->getId()) {
        song->setDateAddedToNow();
        // save / update album. need to do here so we can use id to set album part
        song->getAlbum()->sync();
        if (!song->getAlbum()->getId()) {
            // save album since ID used multiple places
            song->getAlbum()->save();
        }
        dogatech::soulsifter::Album* a = new dogatech::soulsifter::Album(*song->getAlbum());
        song->setAlbum(*a);
        delete a;
        if (song->getAlbumPart()) {
            song->getAlbumPart()->setAlbumId(song->getAlbum()->getId());
            song->getAlbumPart()->sync();
            if (song->getAlbumPart()->getId()) {
              song->setAlbumPartId(song->getAlbumPart()->getId());
            }
        }
        song->save();
        dogatech::soulsifter::MusicManager::getInstance().setNewSongChanges(*song);
        NSDictionary *songDict = [NSDictionary dictionaryWithObjectsAndKeys:[NSValue valueWithPointer:song], UDSPSong, nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:UDSAddedSong
                                                            object:self
                                                          userInfo:songDict];
    } else {
        song->update();
        
        NSString *notificationName = [NSString stringWithFormat:UDSUpdatedSongFormat, song->getId()];
        NSDictionary *songDict = [NSDictionary dictionaryWithObjectsAndKeys:[NSValue valueWithPointer:song], UDSPSong, nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:notificationName
                                                            object:self
                                                          userInfo:songDict];
    }
  delete songAlbum;
  return true;
}

- (IBAction)processMusicFile:(id)sender {
  NSLog(@"tagInfoController.processMusicFile");
    
  if ([self processSong]) {
    // if the song has no id, it's a new object and not being used elsewhere
    // TODO is this true?
    // No, we should delete though b/c it means it failed to save. Otherwise, on save & update,
    // it'll have an idea. So we should make sure that the object is disposed elsewhere.
    if (!song->getId()) {
      delete song;
    }
    [self loadNextSong];
  }
}

- (IBAction)skipMusicFile:(id)sender {
  NSLog(@"skipMusicFile");
  
  // if the song has no id, it was never saved and we should delete the object
  if (!song->getId()) {
    delete song;
  }
  [self loadNextSong];
}

- (IBAction)trashMusicFile:(id)sender {
  NSLog(@"trashMusicFile");
    
  if (![self processSong]) return;
    
  NSFileManager *fileManager = [NSFileManager defaultManager];
  NSURL *oldPath = [NSURL fileURLWithPath:[NSString stringWithUTF8String:song->getFilepath().c_str()]];
  std::string newPath = song->getFilepath() + ".txt";
  if (![fileManager createFileAtPath:[NSString stringWithUTF8String:newPath.c_str()]
                            contents:nil
                          attributes:nil]) {
    NSBeep();
    // TODO can't tell by id, then how do we tell?
    if (!song->getId()) {
      delete song;
    }
    return;
  }
    
  song->setTrashed(true);
  song->setFilepath(newPath);
  song->update();
    
  [fileManager trashItemAtURL:oldPath resultingItemURL:nil error:nil];
  
  // TODO can't tell by id, then how do we tell?
  if (!song->getId()) {
    delete song;
  }
  
  [self loadNextSong];
}

- (void)setFieldsAndUpdate:(BOOL)update {
    dogatech::soulsifter::Song *updatedSong = update ? dogatech::soulsifter::MusicManager::getInstance().updateSongWithChanges(*song) : song;
    [artist setStringValue:[NSString stringWithUTF8String:updatedSong->getArtist().c_str()]];
    [trackNum setStringValue:[NSString stringWithUTF8String:updatedSong->getTrack().c_str()]];
    [title setStringValue:[NSString stringWithUTF8String:updatedSong->getTitle().c_str()]];
    [remixer setStringValue:[NSString stringWithUTF8String:updatedSong->getRemixer().c_str()]];
    [comments setStringValue:[NSString stringWithUTF8String:updatedSong->getComments().c_str()]];
    [rating setIntValue:updatedSong->getRating()];
    [albumArtist setStringValue:[NSString stringWithUTF8String:updatedSong->getAlbum()->getArtist().c_str()]];
    [album setStringValue:[NSString stringWithUTF8String:updatedSong->getAlbum()->getName().c_str()]];
    [label setStringValue:[NSString stringWithUTF8String:updatedSong->getAlbum()->getLabel().c_str()]];
    [catalogId setStringValue:[NSString stringWithUTF8String:updatedSong->getAlbum()->getCatalogId().c_str()]];
    [releaseDateYear setStringValue:[NSString stringWithFormat:@"%i",updatedSong->getAlbum()->getReleaseDateYear()]];
    [releaseDateMonth setStringValue:[NSString stringWithFormat:@"%i",updatedSong->getAlbum()->getReleaseDateMonth()]];
    [releaseDateDay setStringValue:[NSString stringWithFormat:@"%i",updatedSong->getAlbum()->getReleaseDateDay()]];
    [mixed setState:(updatedSong->getAlbum()->getMixed()) ? NSOnState : NSOffState];
    
    const dogatech::soulsifter::BasicGenre* basicGenre = updatedSong->getAlbum()->getBasicGenre();
    if (!basicGenre) basicGenre = dogatech::soulsifter::MusicManager::getInstance().findBasicGenreForArtist(updatedSong->getArtist());
    if (basicGenre) [genreComboBox setStringValue:[NSString stringWithUTF8String:basicGenre->getName().c_str()]];
    
    [artistTag setStringValue:[NSString stringWithUTF8String:song->getArtist().c_str()]];
    [trackNumTag setStringValue:[NSString stringWithUTF8String:song->getTrack().c_str()]];
    [titleTag setStringValue:[NSString stringWithUTF8String:song->getTitle().c_str()]];
    [remixerTag setStringValue:[NSString stringWithUTF8String:song->getRemixer().c_str()]];
    [commentsTag setStringValue:[NSString stringWithUTF8String:song->getComments().c_str()]];
    [albumArtistTag setStringValue:[NSString stringWithUTF8String:song->getAlbum()->getArtist().c_str()]];
    [albumTag setStringValue:[NSString stringWithUTF8String:song->getAlbum()->getName().c_str()]];
    
    [styles deselectAll:self];
    [styles expandItem:nil expandChildren:YES];
    NSMutableArray* styleItems = [NSMutableArray array];
    for (vector<dogatech::soulsifter::Style*>::const_iterator it = updatedSong->getStyles().begin(); it != updatedSong->getStyles().end(); ++it) {
        for (NSUInteger idx = 0; idx < [styles numberOfRows]; idx = ++idx) {
            StyleTreeItem *item = [styles itemAtRow:idx];
            dogatech::soulsifter::Style *style = [item style];
            if ((*it)->getId() == style->getId()) {
                [styleItems addObject:item];
                continue;
            }
        }
    }
    [styles collapseItem:nil collapseChildren:YES];
    for (StyleTreeItem *item in styleItems) {
        [styles selectItem:item];
    }
    
    const dogatech::soulsifter::AlbumPart* albumPart = updatedSong->getAlbumPart();
    if (albumPart) {
        [albumPartOfSet setStringValue:[NSString stringWithUTF8String:albumPart->getPos().c_str()]];
        [albumPartName setStringValue:[NSString stringWithUTF8String:albumPart->getName().c_str()]];
    } else {
        [albumPartOfSet setStringValue:@""];
        [albumPartName setStringValue:@""];
    }
  
  [filePath setStringValue:[NSString stringWithUTF8String:updatedSong->getFilepath().substr(updatedSong->getFilepath().rfind('/') + 1).c_str()]];
    
  delete basicGenre;
  //if (update) delete updatedSong;
}

# pragma mark accessors

@synthesize fileUrls;
@synthesize filesToTrash;
@synthesize genreOptions;

@synthesize filePath;

@synthesize artist;
@synthesize trackNum;
@synthesize title;
@synthesize remixer;
@synthesize comments;
@synthesize rating;
@synthesize albumArtist;
@synthesize album;
@synthesize albumPartOfSet;
@synthesize albumPartName;
@synthesize label;
@synthesize catalogId;
@synthesize releaseDateYear;
@synthesize releaseDateMonth;
@synthesize releaseDateDay;
@synthesize mixed;
@synthesize styles;

@synthesize artistTag;
@synthesize trackNumTag;
@synthesize titleTag;
@synthesize remixerTag;
@synthesize commentsTag;
@synthesize albumArtistTag;
@synthesize albumTag;

@synthesize imageView;

@end
