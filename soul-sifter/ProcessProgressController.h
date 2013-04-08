//
//  ProcessProgressController.h
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#import <Foundation/Foundation.h>

#include "RapidEvolutionMusicDatabaseReader.h"
#include "TagWriter.h"

@interface ProcessProgressController : NSWindowController {
@public
    IBOutlet NSProgressIndicator *progressIndicator;
    soulsifter::RapidEvolutionMusicDatabaseReader *musicDatabaseReader;
    soulsifter::TagWriter *tagWriter;
}

- (IBAction)showWindow:(id)sender;
- (IBAction)readRapidEvolutionDatabase:(id)sender;
- (IBAction)updateBasicGenres:(id)sender;
- (IBAction)exportToRapidEvolutionDatabase:(id)sender;
- (IBAction)flushStagingDirectory:(id)sender;
- (IBAction)writeTags:(id)sender;

@end
