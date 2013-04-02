//
//  SongWrapper.m
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import "SongWrapper.h"

@implementation SongWrapper

# pragma mark initialization

- (SongWrapper *)initWithSong:(soulsifter::Song *)song_ {
    [super init];
    
    self->song = song_;
    artist = [[NSString stringWithUTF8String:song->getArtist().c_str()] copy];
    title = [[NSString stringWithUTF8String:song->getTitle().c_str()] copy];
    
    return self;
}

# pragma mark accessors

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

@end
