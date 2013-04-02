//
//  AppController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CollectionController;
@class DropBox;
@class PreferencesController;
@class ProcessProgressController;
@class TagInfoController;

@interface AppController : NSObject {
@private
    IBOutlet DropBox *dropBox;
    
    CollectionController *collectionController;
    PreferencesController *preferencesController;
    ProcessProgressController *processProgressController;
    TagInfoController *tagInfoController;
}

- (IBAction)showPreferencesPanel:(id)sender;
- (IBAction)showTagInfoWindow:(id)sender;
- (IBAction)showProcessProgressWindow:(id)sender;
- (IBAction)showCollectionWindow:(id)sender;

- (IBAction)populateStagingDirectory:(id)sender;
- (IBAction)flushStagingDirectory:(id)sender;
- (IBAction)readRapidEvolutionDatabase:(id)sender;
- (IBAction)updateBasicGenres:(id)sender;
- (IBAction)exportToRapidEvolutionDatabase:(id)sender;
- (IBAction)writeTags:(id)sender;

@end
