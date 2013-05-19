//
//  SongWrapper.m
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import "SongWrapper.h"

#include "Style.h"

@implementation SongWrapper

# pragma mark initialization

- (SongWrapper *)initWithSong:(soulsifter::Song *)song_ {
    [super init];
    
    self->song = song_;
    artist = [[NSString stringWithUTF8String:song->getArtist().c_str()] copy];
    title = [[NSString stringWithUTF8String:song->getTitle().c_str()] copy];
    rating = [[NSNumber numberWithInt:song->getRating()] copy];
    
    styles = @"";
    vector<soulsifter::Style*> s = song->getStyles();
    for (vector<soulsifter::Style*>::iterator it = s.begin(); it != s.end(); ++it) {
        styles = [[styles stringByAppendingString:[NSString stringWithUTF8String:(*it)->getName().c_str()]] stringByAppendingString:@", "];
    }
    styles = [styles copy];
    
    return self;
}

# pragma mark accessors

- (soulsifter::Song *)song {
    return song;
}

- (NSString *)artist {
    return artist;
}

- (void)setArtist:(NSString *)artist_ {
    [artist release];
    artist = [artist_ copy];
    song->setArtist([artist UTF8String]);
}

- (NSString *)title {
    return title;
}

- (void)setTitle:(NSString *)title_ {
    [title release];
    title = [title_ copy];
    song->setTitle([title UTF8String]);
}

- (NSNumber *)rating {
    return rating;
}

- (void)setRating:(NSNumber *)rating_ {
    [rating release];
    rating = [rating_ copy];
    // TODO song->setRating(rating);
}

- (NSString *)styles {
    return styles;
}

- (void)setStyles:(NSString *)styles_ {
    [styles release];
    styles = [styles_ copy];
    // TODO song->setStyles([styles UTF8String]);
}

@end
