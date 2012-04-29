//
//  DropBox.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "DropBox.h"

@implementation DropBox

# pragma mark initialization

- (void)awakeFromNib {
    NSLog(@"awakeFromNib");
    [self registerForDraggedTypes:[NSArray arrayWithObject:(NSString *)kUTTypeFileURL]];
}

- (void)dealloc {
	NSLog(@"dealloc");
    // deallocate properties
    [fileUrls release];
    
    [super dealloc];
}

# pragma mark pasteboard

- (BOOL) readFromPasteboard:(NSPasteboard *)pb {
    NSLog(@"readFromPasteboard");
    NSArray *classes = [NSArray arrayWithObject:[NSURL class]];
    NSDictionary *options = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:NSPasteboardURLReadingFileURLsOnlyKey];
    if (![pb canReadObjectForClasses:classes options:options]) {
        return NO;
    }
    [fileUrls release];
    fileUrls = [pb readObjectsForClasses:classes options:options];
    [fileUrls retain];
    return YES;
}

# pragma mark ns dragging destination

- (NSDragOperation)draggingEntered:(id<NSDraggingInfo>)sender {
	NSLog(@"draggingEntered");
    if ([sender draggingSourceOperationMask] & NSDragOperationCopy) {
        return NSDragOperationCopy;
    }
    return NSDragOperationNone;
}

- (BOOL)prepareForDragOperation:(id<NSDraggingInfo>)sender {
    NSLog(@"prepareForDragOperation");
    return TRUE;
}

- (BOOL)performDragOperation:(id<NSDraggingInfo>)sender {
    NSLog(@"performDragOperation");
    return [self readFromPasteboard:[sender draggingPasteboard]];
}

- (void)concludeDragOperation:(id<NSDraggingInfo>)sender {
    NSLog(@"concludeDragOperation");
    for (NSURL *url in fileUrls) {
        NSLog([url path]);
    }
}

# pragma mark accessors

@synthesize fileUrls;

@end
