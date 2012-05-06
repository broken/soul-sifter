//
//  PreferencesController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/29/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PreferencesController : NSWindowController {
@public
    IBOutlet NSTextField *musicPathTextField;
    IBOutlet NSTextField *stagingPathTextField;
}

- (IBAction)changeMusicPath:(id)sender;
- (IBAction)changeStagingPath:(id)sender;
- (IBAction)openPath:(id)sender;

@end
