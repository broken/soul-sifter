//
//  TagInfoController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "FilesToAdd.h"
#include "ImageViewWithFilepath.h"
#include "Song.h"

@interface TagInfoController : NSWindowController {
@private
  bool hasMovedFile;
  NSMutableArray *fileUrls;
  NSMutableArray *filesToTrash;
  dogatech::soulsifter::FilesToAdd *filesToAdd;
  dogatech::soulsifter::Song *song;
  
    IBOutlet NSComboBox *genreComboBox;
    IBOutlet NSArrayController *genreArrayController;
    
    IBOutlet NSTextField *filePath;
    
    IBOutlet NSTextField *artist;
    IBOutlet NSTextField *trackNum;
    IBOutlet NSTextField *title;
    IBOutlet NSTextField *remixer;
    IBOutlet NSTextField *comments;
    IBOutlet NSLevelIndicator *rating;
    IBOutlet NSTextField *albumArtist;
    IBOutlet NSTextField *album;
    IBOutlet NSTextField *albumPartOfSet;
    IBOutlet NSTextField *albumPartName;
    IBOutlet NSTextField *label;
    IBOutlet NSTextField *catalogId;
    IBOutlet NSTextField *releaseDateYear;
    IBOutlet NSTextField *releaseDateMonth;
    IBOutlet NSTextField *releaseDateDay;
    IBOutlet NSButton *mixed;
    IBOutlet NSButton *lowQuality;
    IBOutlet NSButton *compilation;
    IBOutlet NSOutlineView *styles;
    IBOutlet NSTextField *bpm;
    IBOutlet NSTextField *key;
  
    IBOutlet NSTextField *artistTag;
    IBOutlet NSTextField *trackNumTag;
    IBOutlet NSTextField *titleTag;
    IBOutlet NSTextField *remixerTag;
    IBOutlet NSTextField *commentsTag;
    IBOutlet NSTextField *albumArtistTag;
    IBOutlet NSTextField *albumTag;
  
  IBOutlet NSTextField *bpmAnalyzed;
  IBOutlet NSTextField *keyAnalyzed;
  
  IBOutlet ImageViewWithFilepath *imageView;
}

- (void)showWindow:(id)sender withSong:(dogatech::soulsifter::Song *)song;

- (IBAction)processMusicFile:(id)sender;
- (IBAction)skipMusicFile:(id)sender;
- (IBAction)trashMusicFile:(id)sender;
- (IBAction)switchCover:(id)sender;

@property(readwrite,retain,nonatomic) NSArray *fileUrls;
@property(readwrite,retain,nonatomic) NSArray *filesToTrash;
@property(readwrite,retain) NSArray *genreOptions;

@property(readwrite,retain,nonatomic) NSTextField *filePath;

@property(readwrite,retain,nonatomic) NSTextField *artist;
@property(readwrite,retain,nonatomic) NSTextField *trackNum;
@property(readwrite,retain,nonatomic) NSTextField *title;
@property(readwrite,retain,nonatomic) NSTextField *remixer;
@property(readwrite,retain,nonatomic) NSTextField *comments;
@property(readwrite,retain) NSLevelIndicator *rating;
@property(readwrite,retain,nonatomic) NSTextField *albumArtist;
@property(readwrite,retain,nonatomic) NSTextField *album;
@property(readwrite,retain,nonatomic) NSTextField *albumPartOfSet;
@property(readwrite,retain,nonatomic) NSTextField *albumPartName;
@property(readwrite,retain,nonatomic) NSTextField *label;
@property(readwrite,retain,nonatomic) NSTextField *catalogId;
@property(readwrite,retain) NSTextField *releaseDateYear;
@property(readwrite,retain) NSTextField *releaseDateMonth;
@property(readwrite,retain) NSTextField *releaseDateDay;
@property(readwrite,retain) NSButton *mixed;
@property(readwrite,retain) NSButton *lowQuality;
@property(readwrite,retain) NSButton *compilation;
@property(readwrite,retain) NSOutlineView *styles;
@property(readwrite,retain,nonatomic) NSTextField *bpm;
@property(readwrite,retain,nonatomic) NSTextField *key;

@property(readwrite,retain,nonatomic) NSTextField *artistTag;
@property(readwrite,retain,nonatomic) NSTextField *trackNumTag;
@property(readwrite,retain,nonatomic) NSTextField *titleTag;
@property(readwrite,retain,nonatomic) NSTextField *remixerTag;
@property(readwrite,retain,nonatomic) NSTextField *commentsTag;
@property(readwrite,retain,nonatomic) NSTextField *albumArtistTag;
@property(readwrite,retain,nonatomic) NSTextField *albumTag;

@property(readwrite,retain,nonatomic) NSTextField *bpmAnalyzed;
@property(readwrite,retain,nonatomic) NSTextField *keyAnalyzed;

@property(readwrite,retain,nonatomic) ImageViewWithFilepath *imageView;

@end
