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
#include "TagWriter.h"

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
    if (tagWriter != NULL && tagWriter->getSrcLength()) {
        [progressIndicator setMinValue:0.0];
        [progressIndicator setMaxValue:tagWriter->getSrcLength()];
        [progressIndicator setDoubleValue:tagWriter->getSrcOffset()];
        [progressIndicator setIndeterminate:FALSE];
        [self performSelector:@selector(incrementProgressBar:) withObject:self afterDelay:1];
    }
    [self performSelector:@selector(startProgressBar:) withObject:self afterDelay:1];
}

# pragma mark update files

- (IBAction)flushStagingDirectory:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"processProgressController.flushStagingDirectory");
    [self startProgressBar:self];
    [[self window] setTitle:@"Flushing staging directory"];
    soulsifter::MusicManager::getInstance().flushStagingDirectory();
    [[self window] close];
    [pool release];
}

# pragma mark update basic genres

- (IBAction)updateBasicGenres:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [[self window] setTitle:@"Updating Basic Genres"];
    soulsifter::MusicManager::getInstance().updateDatabaseBasicGenres();
    [[self window] close];
    [pool release];
}

# pragma mark read re db

- (void)incrementProgressBar:(id)sender {
    if (!musicDatabaseReader || !musicDatabaseReader->isProcessing()) {
        [progressIndicator stopAnimation:self];
        return;
    }
    if (!tagWriter || !tagWriter->isProcessing()) {
        [progressIndicator stopAnimation:self];
        return;
    }
    
    if (musicDatabaseReader) {
        [progressIndicator setDoubleValue:musicDatabaseReader->getSrcOffset()];
    } else if (tagWriter) {
        [progressIndicator setDoubleValue:tagWriter->getSrcOffset()];
    }
    [self performSelector:@selector(incrementProgressBar:) withObject:self afterDelay:1];
}

- (IBAction)readRapidEvolutionDatabase:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"processProgressController.readRapidEvolutionDatabase");
    musicDatabaseReader = new soulsifter::RapidEvolutionMusicDatabaseReader();
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
    soulsifter::RapidEvolutionMusicDatabaseWriter writer;
    writer.write();
    [[self window] close];
    [pool release];
}

- (IBAction)writeTags:(id)sender {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"writeTags");
    tagWriter = new soulsifter::TagWriter();
    [self startProgressBar:self];
    [[self window] setTitle:@"Writing tags to music files"];
    tagWriter->writeAll();
    delete tagWriter;
    tagWriter = NULL;
    [[self window] close];
    [pool release];
}

@end
