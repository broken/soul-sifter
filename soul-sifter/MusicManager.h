//
//  MusicManager.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NSSong;

@interface MusicManager : NSObject {
@private
    // tags
    NSSong *lastParsedSong;
    NSSong *lastSongFixed;
    
    // paths
    NSArray *basicGenres;
    NSDictionary *artistToGenre;
}

+ (MusicManager *)default;

// tags
- (NSSong *)discoverSong:(NSURL *)musicFile;
- (void)writeTagsToSong:(NSSong *)song;

// paths
- (BOOL)getCopyToPath:(NSString **)path;
- (void)moveSong:(NSSong *)song;
- (void)moveImage:(NSURL *)file;
- (void)populateStagingDirectory;
- (void)flushStagingDirectory;

// paths accessors
- (NSArray *)basicGenres;

// db updates
- (void)updateDatabaseBasicGenres;

@end
