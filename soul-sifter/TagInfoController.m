//
//  TagInfoController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "TagInfoController.h"

#import "MusicManager.h"
#import "Song.h"

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

- (void)windowDidLoad {
    NSLog(@"tagInfoController.windowDidLoad");
    [super windowDidLoad];
    
    if (!musicManager) {
        musicManager = [[MusicManager alloc] init];
    }
    Song *song = [musicManager discoverSong:[fileUrls objectAtIndex:index]];
    if ([song artist]) [artist setStringValue:[song artist]];
    if ([song album]) [album setStringValue:[song album]];
    if ([song title]) [title setStringValue:[song title]];
    if ([song trackNum]) [trackNum setStringValue:[song trackNum]];
    if ([song remix]) [remix setStringValue:[song remix]];
    if ([song featuring]) [featuring setStringValue:[song featuring]];
    if ([song releaseDate]) [releaseDate setStringValue:[song releaseDate]];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

# pragma mark actions

- (IBAction)processMusicFile:(id)sender {
    NSLog(@"tagInfoController.processMusicFile");
    
    // unable to move file if any of these are blank
    if (genre == nil || [artist stringValue] == nil || [album stringValue] == nil) {
        NSBeep();
        return;
    }
    
    // update tag
    Song *song = [[Song alloc] init];
    [song autorelease];
    [song setArtist:[artist stringValue]];
    [song setAlbum:[album stringValue]];
    [song setTitle:[title stringValue]];
    [song setTrackNum:[trackNum stringValue]];
    [song setRemix:[remix stringValue]];
    [song setFeaturing:[featuring stringValue]];
    [song setReleaseDate:[releaseDate stringValue]];
    [musicManager writeTags:song toFile:[fileUrls objectAtIndex:index]];
    
    // close window (for now)
    [self close];
}

# pragma mark accessors

@synthesize fileUrls;

@synthesize artist;
@synthesize album;
@synthesize trackNum;
@synthesize title;
@synthesize remix;
@synthesize featuring;
@synthesize releaseDate;
@synthesize label;
@synthesize catalogId;
@synthesize genre;

// Side effect - resets index to 0
- (void)setFileUrls:(NSArray *)newFileUrls {
    NSLog(@"tagInfoController.setFileUrls");
    index = 0;
    [newFileUrls retain];
    [fileUrls release];
    fileUrls = newFileUrls;
}

@end
