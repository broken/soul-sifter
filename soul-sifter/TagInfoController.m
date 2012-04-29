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
    NSLog(@"initWithWindow");
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)windowDidLoad {
    NSLog(@"windowDidLoad");
    [super windowDidLoad];
    
    if (!musicManager) {
        musicManager = [[MusicManager alloc] init];
    }
    song = [musicManager discoverSong:[fileUrls objectAtIndex:index]];
    [artist setStringValue:[song artist]];
    [album setStringValue:[song album]];
    [title setStringValue:[song title]];
    [trackNum setStringValue:[song trackNum]];
    [remix setStringValue:[song remix]];
    [featuring setStringValue:[song featuring]];
    [releaseDate setStringValue:[song releaseDate]];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

# pragma mark accessors

@synthesize song;
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


// Side effect - resets index to 0
- (void)setFileUrls:(NSArray *)newFileUrls {
    NSLog(@"setFileUrls");
    index = 0;
    [newFileUrls retain];
    [fileUrls release];
    fileUrls = newFileUrls;
}

@end
