//
//  RapidEvolutionManager.m
//  soul-sifter
//
//  Created by Robby Neale on 6/25/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "RapidEvolutionManager.h"

#import "Constants.h"
#import "Song.h"


@implementation RapidEvolutionManager

# pragma mark initialization

+ (RapidEvolutionManager *)default {
    static dispatch_once_t pred;
    static RapidEvolutionManager *rapidEvolutionManager = nil;
    dispatch_once(&pred, ^{
        rapidEvolutionManager = [[RapidEvolutionManager alloc] init];
    });
    return rapidEvolutionManager;
}

- (void)writeSongToXml:(Song *)song {
    NSLog(@"rapidEvolutionManager.writeSongToXml");
    
    NSString *path = [[NSUserDefaults standardUserDefaults] stringForKey:UDStagingPath];
    NSString *filePath = [NSString stringWithFormat:@"%@/staging_music_database.xml", path];
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForWritingAtPath:filePath];
    if (!fileHandle) {
        [[NSFileManager defaultManager] createFileAtPath:filePath contents:nil attributes:nil];
        fileHandle = [NSFileHandle fileHandleForWritingAtPath:filePath];
    }
    if (!fileHandle) return;
    
    @try {
        [fileHandle seekToEndOfFile];
        [fileHandle writeData:[@"<song num_excludes=\"0\" num_mixouts=\"0\">\n<unique_id></unique_id>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<songid_winfo>%@ - %@ [%@] %@</songid_winfo>\n",
                                [song artist], [song album], [song trackNum], [song title]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<songid>%@ - %@ [%@] %@</songid>\n",
                                [song artist], [song album], [song trackNum], [song title]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<shortid>%@ - %@</shortid>\n",
                                [song artist], [song title]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<shortid_winfo>%@ - %@</shortid_winfo>\n",
                                [song artist], [song title]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<artist>%@</artist>\n", [song artist]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<album>%@</album>\n", [song album]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<track>%@</track>\n", [song trackNum]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<title>%@</title>\n", [song title]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<time></time>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<time_signature>4/4</time_signature>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<filename>%@</filename>\n", [[song file] path]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<digital_only>yes</digital_only>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<compilation></compilation>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<key_start></key_start>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<key_accuracy></key_accuracy>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<bpm_start></bpm_start>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<bpm_accuracy></bpm_accuracy>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        // TODO rating
        [fileHandle writeData:[@"<rating></rating>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[[NSString stringWithFormat:@"<date_added>%@</date_added>\n", [NSDate date]]
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
        [fileHandle writeData:[@"<styles_bitmask>000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000</styles_bitmask>\n</song>\n"
                               dataUsingEncoding:[NSString defaultCStringEncoding]]];
    }
    @catch (NSException * e) {
        assert(e);
    }
    
    [fileHandle closeFile];
}

@end
