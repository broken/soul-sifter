//
//  ProcessProgressController.m
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#import "ProcessProgressController.h"

#import "Constants.h"
#include "MusicManager.h"
#include "RapidEvolutionMusicDatabaseReader.h"
#include "RapidEvolutionMusicDatabaseWriter.h"

# pragma mark private method helpers

@interface ProcessProgressController()

- (void)startProgressBar:(id)sender;
- (void)incrementProgressBar:(id)sender;

@end

@implementation ProcessProgressController

# pragma mark initialization

- (IBAction)showWindow:(id)sender {
    [[self window] setTitle:@"Process Progress"];
    [[self window] makeKeyAndOrderFront:self];
    [progressIndicator startAnimation:self];
    [progressIndicator setIndeterminate:TRUE];
    [self startProgressBar:self];
}

// this must be able to handle all jobs
- (void)startProgressBar:(id)sender {
    if (musicDatabaseReader != NULL && musicDatabaseReader->getSrcLength()) {
        [progressIndicator setMinValue:0.0];
        [progressIndicator setMaxValue:musicDatabaseReader->getSrcLength()];
        [progressIndicator setDoubleValue:musicDatabaseReader->getSrcOffset()];
        [progressIndicator setIndeterminate:FALSE];
        [self performSelector:@selector(incrementProgressBar:) withObject:self afterDelay:1];
    }
    [self performSelector:@selector(startProgressBar:) withObject:self afterDelay:1];
}

# pragma mark update basic genres

- (IBAction)updateBasicGenres:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [[self window] setTitle:@"Updating Basic Genres"];
    [[MusicManager default] updateDatabaseBasicGenres];
    [[self window] close];
    [pool release];
}

# pragma mark read re db

- (void)incrementProgressBar:(id)sender {
    if (!musicDatabaseReader || !musicDatabaseReader->isProcessing()) {
        [progressIndicator stopAnimation:self];
        return;
    }
    
    [progressIndicator setDoubleValue:musicDatabaseReader->getSrcOffset()];
    [self performSelector:@selector(incrementProgressBar:) withObject:self afterDelay:1];
}

- (IBAction)readRapidEvolutionDatabase:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"processProgressController.readRapidEvolutionDatabase");
    musicDatabaseReader = new RapidEvolutionMusicDatabaseReader();
    [self startProgressBar:self];
    [[self window] setTitle:@"Reading RapidEvolution Database"];
    musicDatabaseReader->read();
    delete musicDatabaseReader;
    musicDatabaseReader = NULL;
    [[self window] close];
    [pool release];
}

- (IBAction)exportToRapidEvolutionDatabase:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"processProgressController.exportToRapidEvolutionDatabase");
    [self startProgressBar:self];
    [[self window] setTitle:@"Exporting to RapidEvolution Database"];
    RapidEvolutionMusicDatabaseWriter writer;
    writer.write();
    [[self window] close];
    [pool release];
}

@end
