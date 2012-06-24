//
//  TagInfoController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "TagInfoController.h"

#import "Constants.h"
#import "MusicManager.h"
#import "Song.h"


# pragma mark private method helpers

@interface TagInfoController()

- (void)loadSong;

@end


@implementation TagInfoController

# pragma mark initialization

- (id)initWithWindow:(NSWindow *)window {
    NSLog(@"tagInfoController.initWithWindow");
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
        musicManager = [MusicManager default];
    }
    
    return self;
}

- (void)dealloc {
    NSLog(@"tagInfoController.dealloc");
    [musicManager release];
    [super dealloc];
}

- (void)windowDidLoad {
    NSLog(@"tagInfoController.windowDidLoad");
    [super windowDidLoad];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    
    [genreArrayController setContent:[musicManager basicGenres]];
}

- (IBAction)showWindow:(id)sender {
    NSLog(@"tagInfoController.showWindow");
    [super showWindow:sender];
    
    // TODO alert if directories don't exist
    
    index = 0;
    [self loadSong];
}

# pragma mark actions

- (IBAction)processMusicFile:(id)sender {
    NSLog(@"tagInfoController.processMusicFile");
    
    // unable to move file if any of these are blank
    if ([genreComboBox stringValue] == nil || [artist stringValue] == nil || [album stringValue] == nil) {
        NSBeep();
        return;
    }
    
    Song *song = [[Song alloc] init];
    [song autorelease];
    [song setFile:[fileUrls objectAtIndex:index]];
    [song setArtist:[artist stringValue]];
    [song setAlbum:[album stringValue]];
    [song setTitle:[title stringValue]];
    [song setTrackNum:[trackNum stringValue]];
    [song setRemix:[remix stringValue]];
    [song setFeaturing:[featuring stringValue]];
    [song setReleaseDateYear:[releaseDateYear stringValue]];
    [song setReleaseDateMonth:[releaseDateMonth stringValue]];
    [song setReleaseDateDay:[releaseDateDay stringValue]];
    [song setBasicGenre:[genreComboBox stringValue]];
    
    // update tag
    [musicManager writeTagsToSong:song];
    
    // move file
    [musicManager moveSong:song];
    
    // load next song
    ++index;
    [self loadSong];
}

- (void)loadSong {
    if (![fileUrls objectAtIndex:index]) {
        // close window
        [self close];
    }
    Song *song = [musicManager discoverSong:[fileUrls objectAtIndex:index]];
    if ([song artist]) [artist setStringValue:[song artist]];
    if ([song album]) [album setStringValue:[song album]];
    if ([song title]) [title setStringValue:[song title]];
    if ([song trackNum]) [trackNum setStringValue:[song trackNum]];
    if ([song remix]) [remix setStringValue:[song remix]];
    if ([song featuring]) [featuring setStringValue:[song featuring]];
    if ([song releaseDateYear]) [releaseDateYear setStringValue:[song releaseDateYear]];
    if ([song releaseDateMonth]) [releaseDateMonth setStringValue:[song releaseDateMonth]];
    if ([song releaseDateDay]) [releaseDateDay setStringValue:[song releaseDateDay]];
    else [releaseDateDay setStringValue:@""];
}

# pragma mark accessors

@synthesize fileUrls;
@synthesize genreOptions;

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

@end
