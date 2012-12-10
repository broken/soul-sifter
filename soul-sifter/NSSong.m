//
//  NSSong.m
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "NSSong.h"

@implementation NSSong

# pragma mark nscopying

- (id)copyWithZone:(NSZone *)zone {
    NSSong *copy = [[NSSong allocWithZone:zone] init];
    [copy setArtist:[artist copyWithZone:zone]];
    [copy setAlbum:[album copyWithZone:zone]];
    [copy setTrackNum:[trackNum copyWithZone:zone]];
    [copy setTitle:[title copyWithZone:zone]];
    [copy setRemix:[remix copyWithZone:zone]];
    [copy setFeaturing:[featuring copyWithZone:zone]];
    [copy setLabel:[label copyWithZone:zone]];
    [copy setCatalogId:[catalogId copyWithZone:zone]];
    [copy setReleaseDateYear:[releaseDateYear copyWithZone:zone]];
    [copy setReleaseDateMonth:[releaseDateMonth copyWithZone:zone]];
    [copy setReleaseDateDay:[releaseDateDay copyWithZone:zone]];
    [copy setBasicGenre:[basicGenre copyWithZone:zone]];
    [copy setFile:[file copyWithZone:zone]];
    return copy;
}

# pragma mark accessors

@synthesize artist;
@synthesize album;
@synthesize trackNum;
@synthesize title;
@synthesize remix;
@synthesize featuring;
@synthesize label;
@synthesize catalogId;
@synthesize releaseDateYear;
@synthesize releaseDateMonth;
@synthesize releaseDateDay;

@synthesize basicGenre;
@synthesize file;
@synthesize rating;

@end
