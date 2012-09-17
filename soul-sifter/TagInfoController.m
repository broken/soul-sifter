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
#import "RapidEvolutionManager.h"
#import "Song.h"


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
    
    Song *song = [[Song alloc] init];
    [song autorelease];
    [song setFile:[fileUrls objectAtIndex:index]];
    [song setArtist:[artist stringValue]];
    [song setAlbum:[album stringValue]];
    [song setTrackNum:[trackNum stringValue]];
    [song setTitle:[title stringValue]];
    [song setRemix:[remix stringValue]];
    [song setFeaturing:[featuring stringValue]];
    [song setLabel:[label stringValue]];
    [song setCatalogId:[catalogId stringValue]];
    [song setReleaseDateYear:[releaseDateYear stringValue]];
    [song setReleaseDateMonth:[releaseDateMonth stringValue]];
    [song setReleaseDateDay:[releaseDateDay stringValue]];
    [song setBasicGenre:[genreComboBox stringValue]];
    
    // update tag
    [musicManager writeTagsToSong:song];
    
    // move file
    [musicManager moveSong:song];
    
    // write rapid evolution xml
    [[RapidEvolutionManager default] writeSongToXml:song];
    
    // load next song
    [self loadNextFile];
}

- (void)loadNextFile {
    NSLog(@"tagInfoController.loadNextFile");
    ++index;
    
    // close window if no more files to process
    if ([fileUrls count] <= index) {
        NSLog(@"No more files to process; closing tag info window");
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
            if ([childFileAttribs objectForKey:NSFileType] == NSFileTypeRegular) {
                childFile = [childFile stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                NSURL *url = [NSURL URLWithString:childFile relativeToURL:fileUrl];
                [fileUrls addObject:url];
            }
        }
        [self loadNextFile];
        return;
    }
    
    // straight move images to last directory
    // TODO we should make this smarter
    if ([[[fileUrl pathExtension] lowercaseString] isEqualToString:@"jpg"] ||
        [[[fileUrl pathExtension] lowercaseString] isEqualToString:@"jpeg"] ||
        [[[fileUrl pathExtension] lowercaseString] isEqualToString:@"gif"] ||
        [[[fileUrl pathExtension] lowercaseString] isEqualToString:@"png"]) {
        [musicManager moveImage:fileUrl];
        [self loadNextFile];
        return;
    }
    
    // at this point it should be a normal file that needs processing
    Song *song = [musicManager discoverSong:fileUrl];
    if ([song artist]) [artist setStringValue:[song artist]];
    if ([song album]) [album setStringValue:[song album]];
    if ([song trackNum]) [trackNum setStringValue:[song trackNum]];
    if ([song title]) [title setStringValue:[song title]];
    if ([song remix]) [remix setStringValue:[song remix]];
    if ([song featuring]) [featuring setStringValue:[song featuring]];
    if ([song label]) [label setStringValue:[song label]];
    if ([song catalogId]) [catalogId setStringValue:[song catalogId]];
    if ([song releaseDateYear]) [releaseDateYear setStringValue:[song releaseDateYear]];
    if ([song releaseDateMonth]) [releaseDateMonth setStringValue:[song releaseDateMonth]];
    if ([song releaseDateDay]) [releaseDateDay setStringValue:[song releaseDateDay]];
    else [releaseDateDay setStringValue:@""];
    if ([song basicGenre]) [genreComboBox setStringValue:[song basicGenre]];
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
