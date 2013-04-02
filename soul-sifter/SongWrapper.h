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
@public
    soulsifter::Song *song;
    
    NSString *artist;
    NSString *title;
}

- (SongWrapper *)initWithSong:(soulsifter::Song *)song;

- (NSString *)artist;
- (void)setArtist:(NSString *)artist;
- (NSString *)title;
- (void)setTitle:(NSString *)title;

@end
