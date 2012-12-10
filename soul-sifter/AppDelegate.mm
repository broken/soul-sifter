//
//  AppDelegate.m
//  soul-sifter
//
//  Created by Robby Neale on 4/17/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "AppDelegate.h"

#import "AppController.h"
#import "Constants.h"
#include "SoulSifterSettings.h"

@implementation AppDelegate

# pragma mark initialization

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    soulsifter::SoulSifterSettings::getInstance().setMusicPath([[userDefaults stringForKey:UDMusicPath] UTF8String]);
    soulsifter::SoulSifterSettings::getInstance().setREPath([[userDefaults stringForKey:UDRapidEvolutionPath] UTF8String]);
    soulsifter::SoulSifterSettings::getInstance().setStagingPath([[userDefaults stringForKey:UDStagingPath] UTF8String]);
}

# pragma mark actions

- (IBAction)filesDropped:(id)sender {
    NSLog(@"appDelegate.filesDropped");
    [appController showTagInfoWindow:sender];
}

# pragma mark accessors

@synthesize appController;
@synthesize window = _window;

@end
