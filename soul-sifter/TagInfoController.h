//
//  TagInfoController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class MusicManager;
@class Song;

@interface TagInfoController : NSWindowController {
@private
    int index;
    NSArray *fileUrls;
    MusicManager *musicManager;
    
    IBOutlet NSTextField *artist;
    IBOutlet NSTextField *album;
    IBOutlet NSTextField *trackNum;
    IBOutlet NSTextField *title;
    IBOutlet NSTextField *remix;
    IBOutlet NSTextField *featuring;
    IBOutlet NSTextField *releaseDate;
    IBOutlet NSTextField *label;
    IBOutlet NSTextField *catalogId;
    IBOutlet NSString *genre;
}

- (IBAction)processMusicFile:(id)sender;

@property(retain,nonatomic) NSArray *fileUrls;

@property(readwrite,retain,nonatomic) NSTextField *artist;
@property(readwrite,retain,nonatomic) NSTextField *album;
@property(readwrite,retain,nonatomic) NSTextField *trackNum;
@property(readwrite,retain,nonatomic) NSTextField *title;
@property(readwrite,retain,nonatomic) NSTextField *remix;
@property(readwrite,retain,nonatomic) NSTextField *featuring;
@property(readwrite,retain,nonatomic) NSTextField *releaseDate;
@property(readwrite,retain,nonatomic) NSTextField *label;
@property(readwrite,retain,nonatomic) NSTextField *catalogId;
@property(readwrite,retain,nonatomic) NSString *genre;

@end
