//
//  CollectionController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import <Cocoa/Cocoa.h>

@interface CollectionController : NSWindowController {
@private
    IBOutlet NSArrayController *collectionArrayController;
}

@property(assign) IBOutlet NSArrayController *collectionArrayController;

@end
