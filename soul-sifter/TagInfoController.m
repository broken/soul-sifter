//
//  TagInfoController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "TagInfoController.h"

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
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

@end
