//
//  DropBox.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface DropBox : NSBox <NSDraggingDestination> {
    NSArray *fileUrls;
}

@property(readwrite,retain) NSArray *fileUrls;

@end
