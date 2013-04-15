//
//  CollectionController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import <Cocoa/Cocoa.h>

#include "Song.h"

@class TagInfoController;

@interface CollectionController : NSWindowController {
@private
    TagInfoController *tagInfoController;
    
    IBOutlet NSTableView *collectionTableView;
    IBOutlet NSArrayController *collectionArrayController;
}

- (void)addSongToCollection:(soulsifter::Song *)song;

- (id)initWithWindowNibName:(NSString *)name andTagInfoController:(TagInfoController *)tagInfoController;

- (IBAction)doubleClickAction:(id)sender;

@property(assign) IBOutlet NSTableView *collectionTableView;
@property(assign) IBOutlet NSArrayController *collectionArrayController;

@end
