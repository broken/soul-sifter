//
//  TagInfoController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface TagInfoController : NSWindowController {
@private
    int index;
    bool hasMovedFile;
    NSMutableArray *fileUrls;
    NSMutableArray *filesToTrash;
    
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
    IBOutlet NSTextField *label;
    IBOutlet NSTextField *catalogId;
    IBOutlet NSTextField *releaseDateYear;
    IBOutlet NSTextField *releaseDateMonth;
    IBOutlet NSTextField *releaseDateDay;
    IBOutlet NSButton *mixed;
    IBOutlet NSOutlineView *styles;
}

- (IBAction)processMusicFile:(id)sender;
- (IBAction)skipMusicFile:(id)sender;

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
@property(readwrite,retain,nonatomic) NSTextField *label;
@property(readwrite,retain,nonatomic) NSTextField *catalogId;
@property(readwrite,retain) NSTextField *releaseDateYear;
@property(readwrite,retain) NSTextField *releaseDateMonth;
@property(readwrite,retain) NSTextField *releaseDateDay;
@property(readwrite,retain) NSButton *mixed;
@property(readwrite,retain) NSOutlineView *styles;

@end
