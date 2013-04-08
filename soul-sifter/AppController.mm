//
//  AppController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "AppController.h"

#import "CollectionController.h"
#import "DropBox.h"
#include "MusicManager.h"
#import "PreferencesController.h"
#import "ProcessProgressController.h"
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

- (IBAction)showProcessProgressWindow:(id)sender {
    NSLog(@"appController.showProcessProgressWindow");
    if (!processProgressController) {
        processProgressController = [[ProcessProgressController alloc] initWithWindowNibName:@"ProcessProgress"];
    }
    [processProgressController showWindow:self];
}

- (IBAction)showCollectionWindow:(id)sender {
    NSLog(@"appController.showCollectionWindow");
    if (!tagInfoController) {
        tagInfoController = [[TagInfoController alloc] initWithWindowNibName:@"TagInfo"];
    }
    if (!collectionController) {
        collectionController = [[CollectionController alloc] initWithWindowNibName:@"Collection" andTagInfoController:tagInfoController];
    }
    [collectionController showWindow:self];
}

- (IBAction)populateStagingDirectory:(id)sender {
    NSLog(@"appController.populateStagingDirectory");
    //TODO [[MusicManager default] populateStagingDirectory];
}

- (IBAction)flushStagingDirectory:(id)sender {
    NSLog(@"appController.flushStagingDirectory");
    [self showProcessProgressWindow:self];
    [NSThread detachNewThreadSelector:@selector(flushStagingDirectory:)
                             toTarget:processProgressController
                           withObject:self];
}

- (IBAction)readRapidEvolutionDatabase:(id)sender {
    NSLog(@"appController.readRapidEvolutionDatabase");
    [self showProcessProgressWindow:self];
    [NSThread detachNewThreadSelector:@selector(readRapidEvolutionDatabase:)
                             toTarget:processProgressController
                           withObject:self];
}

- (IBAction)updateBasicGenres:(id)sender {
    NSLog(@"appController.updateBasicGenres");
    [self showProcessProgressWindow:self];
    [NSThread detachNewThreadSelector:@selector(updateBasicGenres:)
                             toTarget:processProgressController
                           withObject:self];
}

- (IBAction)exportToRapidEvolutionDatabase:(id)sender {
    NSLog(@"exportToRapidEvolutionDatabase");
    [self showProcessProgressWindow:self];
    [NSThread detachNewThreadSelector:@selector(exportToRapidEvolutionDatabase:)
                             toTarget:processProgressController
                           withObject:self];
}

- (IBAction)writeTags:(id)sender {
    NSLog(@"writeTags");
    [self showProcessProgressWindow:self];
    [NSThread detachNewThreadSelector:@selector(writeTags:)
                             toTarget:processProgressController
                           withObject:self];
}

# pragma mark accessors

@end
