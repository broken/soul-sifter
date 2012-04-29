//
//  MusicManager.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Song;

@interface MusicManager : NSObject {
@private
    Song *lastParsedSong;
    Song *lastSongFixed;
}

- (Song *)discoverSong:(NSURL *)musicFile;
- (void)writeTags:(Song *)song toFile:(NSURL *)musicFile;

@end
