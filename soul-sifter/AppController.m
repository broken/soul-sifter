//
//  AppController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "AppController.h"

#import "DropBox.h"
#import "MusicManager.h"
#import "PreferencesController.h"
#import "TagInfoController.h"

@implementation AppController

# pragma mark windows

- (IBAction)showPreferencesPanel:(id)sender {
	NSLog(@"appController.showPreferencesPanel");
	//[self setGenerateCoverLabel:NO];
	if (!preferencesController) {
		preferencesController = [[PreferencesController alloc] init];
	}
	[preferencesController showWindow:self];
}

- (IBAction)showTagInfoWindow:(id)sender {
    NSLog(@"appController.showTagInfoWindow");
    if (!tagInfoController) {
        tagInfoController = [[TagInfoController alloc] initWithWindowNibName:@"TagInfo"];
    }
    [tagInfoController setFileUrls:[dropBox fileUrls]];
    [tagInfoController showWindow:self];
}

- (IBAction)populateStagingDirectory:(id)sender {
    NSLog(@"appController.populateStagingDirectory");
    [[MusicManager default] populateStagingDirectory];
}

@end
