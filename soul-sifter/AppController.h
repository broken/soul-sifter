//
//  AppController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DropBox;
@class PreferencesController;
@class ProcessProgressController;
@class TagInfoController;

@interface AppController : NSObject {
@private
    IBOutlet DropBox *dropBox;
    
    PreferencesController *preferencesController;
    TagInfoController *tagInfoController;
    ProcessProgressController *processProgressController;
}

- (IBAction)showPreferencesPanel:(id)sender;
- (IBAction)showTagInfoWindow:(id)sender;
- (IBAction)showProcessProgressWindow:(id)sender;

- (IBAction)populateStagingDirectory:(id)sender;
- (IBAction)flushStagingDirectory:(id)sender;
- (IBAction)readRapidEvolutionDatabase:(id)sender;
- (IBAction)updateBasicGenres:(id)sender;

@end
