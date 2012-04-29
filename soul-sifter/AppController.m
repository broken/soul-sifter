//
//  AppController.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "AppController.h"
#import "TagInfoController.h"

@implementation AppController

# pragma mark windows

- (IBAction)showTagInfoWindow:(id)sender {
    NSLog(@"showTagInfoWindow");
    if (!tagInfoController) {
        tagInfoController = [[TagInfoController alloc] initWithWindowNibName:@"TagInfo"];
    }
    [tagInfoController showWindow:self];
}

@end
