//
//  PathButton.m
//  soul-sifter
//
//  Created by Robby Neale on 5/6/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "PathButton.h"

@implementation PathButton

# pragma mark initialization

- (void)dealloc {
    [pathTextField release];
    
    [super dealloc];
}

# pragma mark accessors

@synthesize pathTextField;

@end
