//
//  ProcessProgressController.h
//  soul-sifter
//
//  Created by Robby Neale on 11/26/12.
//
//

#import <Foundation/Foundation.h>

#include "RapidEvolutionMusicDatabaseReader.h"

@interface ProcessProgressController : NSWindowController {
@public
    IBOutlet NSProgressIndicator *progressIndicator;
    RapidEvolutionMusicDatabaseReader *musicDatabaseReader;
}

- (IBAction)showWindow:(id)sender;
- (IBAction)readRapidEvolutionDatabase:(id)sender;

@end
