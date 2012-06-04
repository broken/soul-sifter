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
    // tags
    Song *lastParsedSong;
    Song *lastSongFixed;
    
    // paths
    NSArray *basicGenres;
    NSDictionary *artistToGenre;
}

+ (MusicManager *)default;

// tags
- (Song *)discoverSong:(NSURL *)musicFile;
- (void)writeTagsToSong:(Song *)song;

// paths
- (void)moveSong:(Song *)song;
- (void)populateStagingDirectory;

// paths accessors
- (NSArray *)basicGenres;

@end
