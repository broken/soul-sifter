//
//  ProcessProgressController.m
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#import "ProcessProgressController.h"

#import "Constants.h"
#include "RapidEvolutionMusicDatabaseReader.h"

# pragma mark private method helpers

@interface ProcessProgressController()

- (void)startProgressBar:(id)sender;
- (void)setProgressBar:(id)sender;
- (void)incrementProgressBar:(id)sender;

@end

@implementation ProcessProgressController

# pragma mark initialization

- (IBAction)showWindow:(id)sender {
    musicDatabaseReader = new RapidEvolutionMusicDatabaseReader();
    [NSThread detachNewThreadSelector:@selector(readRapidEvolutionDatabase:) toTarget:self withObject:self];
    [[self window] makeKeyAndOrderFront:self];
    [self startProgressBar:self];
}

# pragma mark progress bar

- (void)startProgressBar:(id)sender {
    [progressIndicator startAnimation:self];
    [progressIndicator setIndeterminate:TRUE];
    [self performSelector:@selector(setProgressBar:) withObject:self afterDelay:1];
}

- (void)setProgressBar:(id)sender {
    if (!musicDatabaseReader->isProcessing()) {
        [progressIndicator stopAnimation:self];
        delete musicDatabaseReader;
        return;
    }
    
    if (!musicDatabaseReader->getSrcLength()) {
        [self performSelector:@selector(preprocessingProgressBar:) withObject:self afterDelay:1];
        return;
    }
    
    [progressIndicator setMinValue:0.0];
    [progressIndicator setMaxValue:musicDatabaseReader->getSrcLength()];
    [progressIndicator setDoubleValue:musicDatabaseReader->getSrcOffset()];
    [progressIndicator setIndeterminate:FALSE];
    [self performSelector:@selector(incrementProgressBar:) withObject:self afterDelay:1];
}

- (void)incrementProgressBar:(id)sender {
    if (!musicDatabaseReader->isProcessing()) {
        [progressIndicator stopAnimation:self];
        delete musicDatabaseReader;
        return;
    }
    
    [progressIndicator setDoubleValue:musicDatabaseReader->getSrcOffset()];
    [self performSelector:@selector(incrementProgressBar:) withObject:self afterDelay:1];
}

# pragma mark read db

- (IBAction)readRapidEvolutionDatabase:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"processProgressController.readRapidEvolutionDatabase");
    musicDatabaseReader->read();
    [[self window] close];
    [pool release];
}

@end
