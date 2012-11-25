//
//  ArchiveUtil.m
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#import "ArchiveUtil.h"

#import "NSString+MD5.h"

@implementation ArchiveUtil

+(NSURL *)unrarFile:(NSURL *)fileUrl {
    NSLog(@"archiveUtil.unrarFile");
    NSString *outputPath = [[fileUrl path] MD5];
    
    // prepare unrar task
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/usr/local/bin/unrar"];
	[task setCurrentDirectoryPath:[[fileUrl URLByDeletingLastPathComponent] path]];
	NSArray *args = [NSArray arrayWithObjects:@"-o+", [fileUrl lastPathComponent], outputPath, nil];
	[task setArguments:args];
	
    // create the pipe to read from
	NSPipe *outPipe = [[NSPipe alloc] init];
	[task setStandardOutput:outPipe];
	[outPipe release];
	
    // unrar
	[task launch];
	
    // read the output
	NSData *data = [[outPipe fileHandleForReading] readDataToEndOfFile];
	
    // make sure the task terminated normally
	[task waitUntilExit];
	int status = [task terminationStatus];
	[task release];
	
    // check status
	NSString *output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
	NSLog(@"unrar ended with status %i & output:\n%@", status, output);
	[output release];
    
    // return output path
    return [NSURL URLWithString:outputPath relativeToURL:[fileUrl URLByDeletingLastPathComponent]];
}

+(void)unrarFile:(NSString *)file toPath:(NSString *)path {
    NSLog(@"archiveUtil.unrarFile.toPath");
    
    // prepare unrar task
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/usr/local/bin/unrar"];
	[task setCurrentDirectoryPath:path];
	NSArray *args = [NSArray arrayWithObjects:@"-e", [file lastPathComponent], nil];
	[task setArguments:args];
	
    // create the pipe to read from
	NSPipe *outPipe = [[NSPipe alloc] init];
	[task setStandardOutput:outPipe];
	[outPipe release];
	
    // unrar
	[task launch];
	
    // read the output
	NSData *data = [[outPipe fileHandleForReading] readDataToEndOfFile];
	
    // make sure the task terminated normally
	[task waitUntilExit];
	int status = [task terminationStatus];
	[task release];
	
    // check status
	NSString *output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
	NSLog(@"unrar ended with status %i & output:\n%@", status, output);
	[output release];
}

+(NSURL *)unzipFile:(NSURL *)fileUrl {
    NSLog(@"archiveUtil.unzipFile");
    NSString *outputPath = [[fileUrl path] MD5];
    
    // prepare unrar task
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/usr/bin/unzip"];
	[task setCurrentDirectoryPath:[[fileUrl URLByDeletingLastPathComponent] path]];
	NSArray *args = [NSArray arrayWithObjects: @"-o", [fileUrl lastPathComponent], @"-d", outputPath, nil];
	[task setArguments:args];
	
    // create the pipe to read from
	NSPipe *outPipe = [[NSPipe alloc] init];
	[task setStandardOutput:outPipe];
	[outPipe release];
	
    // unrar
	[task launch];
	
    // read the output
	NSData *data = [[outPipe fileHandleForReading] readDataToEndOfFile];
	
    // make sure the task terminated normally
	[task waitUntilExit];
	int status = [task terminationStatus];
	[task release];
	
    // check status
	NSString *output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
	NSLog(@"unzip ended with status %i & output:\n%@", status, output);
	[output release];
    
    // return output path
    return [NSURL URLWithString:outputPath relativeToURL:[fileUrl URLByDeletingLastPathComponent]];
}

+(void)unzipFile:(NSString *)file toPath:(NSString *)path {
    NSLog(@"archiveUtil.unzipFile");
    
    // prepare unrar task
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/usr/bin/unzip"];
	[task setCurrentDirectoryPath:path];
	NSArray *args = [NSArray arrayWithObjects:@"-j", [file lastPathComponent], nil];
	[task setArguments:args];
	
    // create the pipe to read from
	NSPipe *outPipe = [[NSPipe alloc] init];
	[task setStandardOutput:outPipe];
	[outPipe release];
	
    // unzip
	[task launch];
	
    // read the output
	NSData *data = [[outPipe fileHandleForReading] readDataToEndOfFile];
	
    // make sure the task terminated normally
	[task waitUntilExit];
	int status = [task terminationStatus];
	[task release];
	
    // check status
	NSString *output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
	NSLog(@"unzip ended with status %i & output:\n%@", status, output);
	[output release];
}

@end
