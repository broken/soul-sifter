//
//  NSSong.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSSong : NSObject <NSCopying> {
@private
    NSString *artist;
    NSString *album;
    NSString *trackNum;
    NSString *title;
    NSString *remix;
    NSString *featuring;
    NSString *label;
    NSString *catalogId;
    NSString *releaseDateYear;
    NSString *releaseDateMonth;
    NSString *releaseDateDay;
    
    NSString *basicGenre;
    NSURL *file;
}

@property(readwrite,retain) NSString *artist;
@property(readwrite,retain) NSString *album;
@property(readwrite,retain) NSString *trackNum;
@property(readwrite,retain) NSString *title;
@property(readwrite,retain) NSString *remix;
@property(readwrite,retain) NSString *featuring;
@property(readwrite,retain) NSString *label;
@property(readwrite,retain) NSString *catalogId;
@property(readwrite,retain) NSString *releaseDateYear;
@property(readwrite,retain) NSString *releaseDateMonth;
@property(readwrite,retain) NSString *releaseDateDay;

@property(readwrite,retain) NSString *basicGenre;
@property(readwrite,retain) NSURL *file;

- (id)copyWithZone:(NSZone *)zone;

@end
