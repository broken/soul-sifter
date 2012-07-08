//
//  PreferencesController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/29/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PreferencesController : NSWindowController <NSWindowDelegate> {
@public
    IBOutlet NSTextField *musicPathTextField;
    IBOutlet NSTextField *rapidEvolutionPathTextField;
    IBOutlet NSTextField *stagingPathTextField;
}

- (IBAction)openPath:(id)sender;

@end
