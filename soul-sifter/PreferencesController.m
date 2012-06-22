//
//  PreferencesController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/29/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "PreferencesController.h"

#import "Constants.h"
#import "MusicManager.h"
#import "PathButton.h"


# pragma mark private method helpers

@interface PreferencesController()

- (void)changeMusicPath:(id)sender;
- (void)changeStagingPath:(id)sender;

@end


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
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	NSString *musicPath = [defaults stringForKey:UDMusicPath];
	NSString *stagingPath = [defaults stringForKey:UDStagingPath];
	[musicPathTextField setStringValue:musicPath ? musicPath : @""];
	[stagingPathTextField setStringValue:stagingPath ? stagingPath : @""];
}

-(void)windowWillClose:(NSNotification *)notification {
    NSLog(@"preferencesController.windowWillClose");
    [self changeMusicPath:self];
    [self changeStagingPath:self];
    [[MusicManager default] populateStagingDirectory];
}

# pragma mark actions

- (void)changeMusicPath:(id)sender {
	NSLog(@"preferencesController.changeMusicPath");
	NSString *text = [musicPathTextField stringValue];
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[defaults setObject:text forKey:UDMusicPath];
}

- (void)changeStagingPath:(id)sender {
	NSLog(@"preferencesController.changeStagingPath");
	NSString *text = [stagingPathTextField stringValue];
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[defaults setObject:text forKey:UDStagingPath];
}

- (IBAction)openPath:(id)sender {
	NSLog(@"preferencesController.openPath");
    PathButton *btn = sender;
	
    // programatically create open (file) panel
	NSOpenPanel *openPanel = [NSOpenPanel openPanel];
	[openPanel setCanChooseFiles:NO];
    [openPanel setCanCreateDirectories:YES];
	[openPanel setCanChooseDirectories:YES];
	[openPanel setAllowsMultipleSelection:NO];
    [openPanel setDirectoryURL:[NSURL fileURLWithPath:[[btn pathTextField] stringValue] isDirectory:YES]];
    [openPanel setAllowedFileTypes:nil];
	[openPanel setTitle:@"Select folder..."];
	
    // Display the dialog. If the OK button was pressed, set the new directory;
	if ([openPanel runModal] == NSOKButton) {
		[[btn pathTextField] setStringValue:[[openPanel directoryURL] path]];
	}
}

@end
