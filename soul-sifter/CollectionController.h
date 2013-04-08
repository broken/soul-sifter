//
//  CollectionController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import <Cocoa/Cocoa.h>

@class TagInfoController;

@interface CollectionController : NSWindowController {
@private
    TagInfoController *tagInfoController;
    
    IBOutlet NSTableView *collectionTableView;
    IBOutlet NSArrayController *collectionArrayController;
}

- (id)initWithWindowNibName:(NSString *)name andTagInfoController:(TagInfoController *)tagInfoController;

- (IBAction)doubleClickAction:(id)sender;

@property(assign) IBOutlet NSTableView *collectionTableView;
@property(assign) IBOutlet NSArrayController *collectionArrayController;

@end
