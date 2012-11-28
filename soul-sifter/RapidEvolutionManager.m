//
//  RapidEvolutionManager.m
//  soul-sifter
//
//  Created by Robby Neale on 6/25/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "RapidEvolutionManager.h"

#import "Constants.h"
#import "NSSong.h"

#import "FileReader.h"


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

- (void)flushXml {
    NSLog(@"rapidEvolutionManager.flushXml");
    
    NSString *rePath = [[NSUserDefaults standardUserDefaults] stringForKey:UDRapidEvolutionPath];
    NSString *reFilePath = [NSString stringWithFormat:@"%@/music_database.xml", rePath];
    FileReader *reFileReader = [[FileReader alloc] initWithFilePath:reFilePath];
    if (!reFileReader) {
        NSLog(@"Unable to locate Rapid Evolution music database");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging XML failed"];
        [alert setInformativeText:@"Unable to locate Rapid Evolution music database"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    
    NSString *reTmpFilePath = [NSString stringWithFormat:@"%@/music_database.xml.tmp", rePath];
    [[NSFileManager defaultManager] createFileAtPath:reTmpFilePath contents:nil attributes:nil];
    NSFileHandle *reTmpFileHandle = [NSFileHandle fileHandleForWritingAtPath:reTmpFilePath];
    if (!reTmpFileHandle) {
        [reFileReader release];
        NSLog(@"Unable to create file for temporary Rapid Evolution music database");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging XML failed"];
        [alert setInformativeText:@"Unable to create file for temporary Rapid Evolution music database"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    
    NSString *stagingPath = [[NSUserDefaults standardUserDefaults] stringForKey:UDStagingPath];
    NSString *stagingFilePath = [NSString stringWithFormat:@"%@/staging_music_database.xml", stagingPath];
    FileReader *stagingFileReader = [[FileReader alloc] initWithFilePath:stagingFilePath];
    if (!stagingFileReader) {
        [reFileReader release];
        NSLog(@"Unable to locate staging music database");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging XML failed"];
        [alert setInformativeText:@"Unable to locate staging music database"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    
    // first count the number of songs we are adding
    int numSongsAdding = 0;
    NSString *line = nil;
    while ((line = [stagingFileReader readLine])) {
        if ([line isEqualToString:@"<unique_id></unique_id>\n"]) ++numSongsAdding;
    };
       
    // copy first section up to songs of music database
    NSError *error = nil;
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"^(<songs .* max_unique_id=\")(\\d*)(\".*)$"
                                                                           options:NSRegularExpressionCaseInsensitive
                                                                             error:&error];
    NSTextCheckingResult *match = nil;
    while ((line = [reFileReader readLine])) {
        if ((match = [regex firstMatchInString:line options:0 range:NSMakeRange(0, [line length])])) {
            NSLog(@"Found songs with line %@", line);
            break;
        }
        [reTmpFileHandle writeData:[line dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    // write new line songs line
    long maxUniqueId = [[line substringWithRange:[match rangeAtIndex:2]] integerValue];
    NSLog(@"new max unique id = %ld", maxUniqueId + numSongsAdding);
    NSString *newLine = [regex stringByReplacingMatchesInString:line
                                                        options:0
                                                          range:NSMakeRange(0, [line length])
                                                   withTemplate:[NSString stringWithFormat:@"$1%ld$3",
                                                                 (maxUniqueId + numSongsAdding)]];
    NSLog(@"new songs line: %@", newLine);
    [reTmpFileHandle writeData:[newLine dataUsingEncoding:NSUTF8StringEncoding]];
    
    // write songs
    [stagingFileReader resetToBeginning];
    while ((line = [stagingFileReader readLine])) {
        if ([line isEqualToString:@"<unique_id></unique_id>\n"]) {
            newLine = [NSString stringWithFormat:@"<unique_id>%d</unique_id>\n", maxUniqueId++];
            [reTmpFileHandle writeData:[newLine dataUsingEncoding:NSUTF8StringEncoding]];
        } else {
            [reTmpFileHandle writeData:[line dataUsingEncoding:NSUTF8StringEncoding]];
        }
    }
    
    // finish outputting previous file
    //[reFileReader enumerateLinesUsingBlock:^(NSSTring *line, BOOL *stop) {
    while ((line = [reFileReader readLine])) {
        [reTmpFileHandle writeData:[line dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    [reFileReader release];
    [stagingFileReader release];
    [reTmpFileHandle closeFile];
    
    // switch files
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSTimeInterval timestamp = [[NSDate date] timeIntervalSince1970];
    NSString *reBackupFilePath = [NSString stringWithFormat:@"%@.%0.0f", reFilePath, timestamp];
    NSLog(@"moving '%@' to '%@'", reFilePath, reBackupFilePath);
    if (![fileManager moveItemAtURL:[NSURL fileURLWithPath:reFilePath]
                              toURL:[NSURL fileURLWithPath:reBackupFilePath]
                              error:&error]) {
        NSString *msg = [NSString stringWithFormat:@"Unable to move Rapid Evolution database file."];
        NSAssert(NO, msg);
    }
    NSLog(@"moving '%@' to '%@'", reTmpFilePath, reFilePath);
    if (![fileManager moveItemAtURL:[NSURL fileURLWithPath:reTmpFilePath]
                              toURL:[NSURL fileURLWithPath:reFilePath]
                              error:&error]) {
        NSString *msg = [NSString stringWithFormat:@"Unable to move temporary Rapid Evolution database file."];
        NSAssert(NO, msg);
    }
    NSString *stagingBackupFilePath = [NSString stringWithFormat:@"%@.%0.0f", stagingFilePath, timestamp];
    NSLog(@"moving '%@' to '%@'", stagingFilePath, stagingBackupFilePath);
    if (![fileManager moveItemAtURL:[NSURL fileURLWithPath:stagingFilePath]
                              toURL:[NSURL fileURLWithPath:stagingBackupFilePath]
                              error:&error]) {
        NSString *msg = [NSString stringWithFormat:@"Unable to move staging file to back."];
        NSAssert(NO, msg);
    }
}

- (void)updateXml {
    NSLog(@"rapidEvolutionManager.updateXml");
    
    NSString *rePath = [[NSUserDefaults standardUserDefaults] stringForKey:UDRapidEvolutionPath];
    NSString *reFilePath = [NSString stringWithFormat:@"%@/music_database.xml", rePath];
    FileReader *reFileReader = [[FileReader alloc] initWithFilePath:reFilePath];
    if (!reFileReader) {
        NSLog(@"Unable to locate Rapid Evolution music database");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging XML failed"];
        [alert setInformativeText:@"Unable to locate Rapid Evolution music database"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    
    NSString *reTmpFilePath = [NSString stringWithFormat:@"%@/music_database.xml.tmp", rePath];
    [[NSFileManager defaultManager] createFileAtPath:reTmpFilePath contents:nil attributes:nil];
    NSFileHandle *reTmpFileHandle = [NSFileHandle fileHandleForWritingAtPath:reTmpFilePath];
    if (!reTmpFileHandle) {
        [reFileReader release];
        NSLog(@"Unable to create file for temporary Rapid Evolution music database");
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"Damn"];
        [alert setMessageText:@"Flushing staging XML failed"];
        [alert setInformativeText:@"Unable to create file for temporary Rapid Evolution music database"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
        [alert release];
        return;
    }
    
    // create regex for substitution
    NSError *error = nil;
    NSString *stagingPath = [[NSUserDefaults standardUserDefaults] stringForKey:UDStagingPath];
    NSString *pattern = [NSRegularExpression escapedPatternForString:stagingPath];
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:pattern
                                                                           options:NSRegularExpressionCaseInsensitive
                                                                             error:&error];
    
    // loop through file and replace directory
    NSString *line;
    NSTextCheckingResult *match = nil;
    NSString *musicPath = [[NSUserDefaults standardUserDefaults] stringForKey:UDMusicPath];
    while ((line = [reFileReader readLine])) {
        if ((match = [regex firstMatchInString:line options:0 range:NSMakeRange(0, [line length])])) {
            NSString *newLine = [regex stringByReplacingMatchesInString:line
                                                                options:0
                                                                  range:NSMakeRange(0, [line length])
                                                           withTemplate:musicPath];
            NSLog(@"Replacing %@\twith %@", line, newLine);
            [reTmpFileHandle writeData:[newLine dataUsingEncoding:NSUTF8StringEncoding]];
        } else {
            [reTmpFileHandle writeData:[line dataUsingEncoding:NSUTF8StringEncoding]];
        }
    }
    
    [reFileReader release];
    [reTmpFileHandle closeFile];
    
    // switch files
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSTimeInterval timestamp = [[NSDate date] timeIntervalSince1970];
    NSString *reBackupFilePath = [NSString stringWithFormat:@"%@.%0.0f", reFilePath, timestamp];
    NSLog(@"moving '%@' to '%@'", reFilePath, reBackupFilePath);
    if (![fileManager moveItemAtURL:[NSURL fileURLWithPath:reFilePath]
                              toURL:[NSURL fileURLWithPath:reBackupFilePath]
                              error:&error]) {
        NSString *msg = [NSString stringWithFormat:@"Unable to move Rapid Evolution database file."];
        NSAssert(NO, msg);
    }
    NSLog(@"moving '%@' to '%@'", reTmpFilePath, reFilePath);
    if (![fileManager moveItemAtURL:[NSURL fileURLWithPath:reTmpFilePath]
                              toURL:[NSURL fileURLWithPath:reFilePath]
                              error:&error]) {
        NSString *msg = [NSString stringWithFormat:@"Unable to move temporary Rapid Evolution database file."];
        NSAssert(NO, msg);
    }
}

- (void)writeSongToXml:(NSSong *)song {
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
