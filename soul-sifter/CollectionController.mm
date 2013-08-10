//
//  CollectionController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import "CollectionController.h"

#import "Constants.h"
#include "Song.h"
#import "SongWrapper.h"
#import "TagInfoController.h"

@implementation CollectionController

# pragma mark initialization

- (id)initWithWindowNibName:(NSString *)name andTagInfoController:(TagInfoController *)tagInfo {
    NSLog(@"tagInfoController.initWithWindowNibName");
    self = [self initWithWindowNibName:name];
    tagInfoController = tagInfo;
    return self;
}

- (id)initWithWindow:(NSWindow *)window {
    NSLog(@"collectionController.initWithWindow");
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(addSongToCollection:)
                                                     name:UDSAddedSong
                                                   object:nil];
    }
    
    return self;
}

- (void)dealloc {
    NSLog(@"collectionController.dealloc");
    [super dealloc];
}

- (void)windowDidLoad {
    NSLog(@"collectionController.windowDidLoad");
    [super windowDidLoad];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.;
    [collectionTableView setDoubleAction:@selector(doubleClickAction:)];
    [self populateCollection];
}

- (void)populateCollection {
    NSLog(@"collectionController.populateCollection");
    
    dogatech::ResultSetIterator<dogatech::soulsifter::Song>* songs = dogatech::soulsifter::Song::findAll();
    dogatech::soulsifter::Song* song = new dogatech::soulsifter::Song();
    while (songs->next(song)) {
        [collectionArrayController addObject:[[SongWrapper alloc] initWithSong:song]];
        song = new dogatech::soulsifter::Song();
    }
    delete song;  // extra
    delete songs;
}

- (void)addSongToCollection:(NSNotification *)notification {
    NSDictionary *dictWithSong = [notification userInfo];
    NSValue *songVal = [dictWithSong valueForKey:UDSPSong];
    dogatech::soulsifter::Song* song = (dogatech::soulsifter::Song*)[songVal pointerValue];
    if ([[collectionArrayController arrangedObjects] count])
        [collectionArrayController addObject:[[SongWrapper alloc] initWithSong:(new dogatech::soulsifter::Song(*song))]];
}

# pragma mark actions

- (IBAction)doubleClickAction:(id)sender {
    dogatech::soulsifter::Song* song = [[[collectionArrayController selectedObjects] objectAtIndex:0] song];
    [tagInfoController showWindow:self withSong:song];
}

# pragma mark accessors

@synthesize collectionTableView;
@synthesize collectionArrayController;

@end
