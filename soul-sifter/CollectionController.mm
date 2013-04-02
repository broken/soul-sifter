//
//  CollectionController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import "CollectionController.h"

#include "Song.h"
#import "SongWrapper.h"

@implementation CollectionController

# pragma mark initialization

- (id)initWithWindow:(NSWindow *)window {
    NSLog(@"collectionController.initWithWindow");
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
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
    [self populateCollection];
}

- (void)populateCollection {
    NSLog(@"collectionController.populateCollection");
    
    dogatech::ResultSetIterator<soulsifter::Song>* songs = soulsifter::Song::findAll();
    soulsifter::Song* song = new soulsifter::Song();
    while (songs->next(song)) {
        /*[collectionArrayController addObject:[NSMutableDictionary dictionaryWithObjectsAndKeys:
         [NSString stringWithUTF8String:song->getArtist().c_str()], @"artist",
         [NSString stringWithUTF8String:song->getTitle().c_str()], @"title",
         nil]];*/
        [collectionArrayController addObject:[[SongWrapper alloc] initWithSong:song]];
        //[collectionArrayController addObject:[NSValue valueWithPointer:song]];
        //MyCPPObject *obj = [[MyArray objectAtIndex:index] pointerValue];
        song = new soulsifter::Song();
    }
    delete song;  // extra
    delete songs;
}

# pragma mark accessors

@synthesize collectionArrayController;

@end
