//
//  AppDelegate.m
//  soul-sifter
//
//  Created by Robby Neale on 4/17/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "AppDelegate.h"

#import "AppController.h"

@implementation AppDelegate

# pragma mark initialization

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}

# pragma mark actions

- (IBAction)filesDropped:(id)sender {
    NSLog(@"filesDropped");
    [appController showTagInfoWindow:sender];
}

# pragma mark accessors

@synthesize appController;
@synthesize window = _window;

@end
