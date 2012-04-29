//
//  PreferencesController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/29/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "PreferencesController.h"

#import "Constants.h"

@implementation PreferencesController

# pragma mark initialization

- (id)init {
	NSLog(@"preferencesController.init");
	if (![super initWithWindowNibName:@"Preferences"]) {
		return nil;
	}
	return self;
}

- (void)windowDidLoad {
	NSLog(@"preferencesController.windowDidLoad");
	[musicPathTextField setStringValue:[self musicPath]];
}

# pragma mark actions

- (IBAction)changeMusicPath:(id)sender {
	NSLog(@"preferencesController.changeMusicPath");
	NSString *text = [musicPathTextField stringValue];
	
    // update defaults
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[defaults setObject:text forKey:UDMusicPath];
	
    // send notification about change
	//[[NSNotificationCenter defaultCenter] postNotificationName:DTMusicPathChangedNotification object:self];
    
    // close window
    [self close];
}

- (IBAction)openPath:(id)sender {
	NSLog(@"preferencesController.openPath");
	
    // programatically create open (file) panel
	NSOpenPanel *openPanel = [NSOpenPanel openPanel];
	[openPanel setCanChooseFiles:NO];
	[openPanel setCanChooseDirectories:YES];
	[openPanel setAllowsMultipleSelection:NO];
    [openPanel setDirectoryURL:[NSURL fileURLWithPath:[self musicPath] isDirectory:YES]];
    [openPanel setAllowedFileTypes:nil];
	[openPanel setTitle:@"Select folder..."];
	
    // Display the dialog. If the OK button was pressed, set the new directory;
	if ([openPanel runModal] == NSOKButton) {
		[musicPathTextField setStringValue:[[openPanel directoryURL] path]];
	}
}

# pragma mark accessors

- (NSString	*)musicPath {
    NSLog(@"preferencesController.musicPath");
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	NSString *musicPath = [defaults stringForKey:UDMusicPath];
    return musicPath ? musicPath : @"";
}

@end
