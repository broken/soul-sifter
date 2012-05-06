//
//  PathButton.h
//  soul-sifter
//
//  Created by Robby Neale on 5/6/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface PathButton : NSButton {
@public
    IBOutlet NSTextField *pathTextField;
}

- (NSTextField *)pathTextField;

@end
