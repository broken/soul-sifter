//
//  AppDelegate.h
//  soul-sifter
//
//  Created by Robby Neale on 4/17/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class AppController;

@interface AppDelegate : NSObject <NSApplicationDelegate> {
@private
    IBOutlet AppController *appController;
}

@property(assign) IBOutlet AppController *appController;
@property(assign) IBOutlet NSWindow *window;

- (IBAction)filesDropped:(id)sender;

@end
