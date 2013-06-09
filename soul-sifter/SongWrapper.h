//
//  SongWrapper.h
//  soul-sifter
//
//  Created by Robby Neale on 4/1/13.
//
//

#import <Foundation/Foundation.h>

#include "Song.h"

@interface SongWrapper : NSObject {
@private
    soulsifter::Song *song;
    
    NSString *artist;
    NSString *title;
    NSNumber *rating;
    NSString *styles;
}

- (SongWrapper *)initWithSong:(soulsifter::Song *)song;

- (void)updateValues:(NSNotification *)unused;

- (soulsifter::Song *)song;
- (NSString *)artist;
- (void)setArtist:(NSString *)artist;
- (NSString *)title;
- (void)setTitle:(NSString *)title;
- (NSNumber *)rating;
- (void)setRating:(NSNumber *)rating;
- (NSString *)styles;
- (void)setStyles:(NSString *)styles;

@end
