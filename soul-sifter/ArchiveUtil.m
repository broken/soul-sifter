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
  NSFileManager* fileManager = [NSFileManager defaultManager];
  NSError *error;
  
  // create work dir
  NSURL *workDir = [NSURL fileURLWithPathComponents:
                    [NSArray arrayWithObjects:
                     [[fileUrl URLByDeletingLastPathComponent] path], [[fileUrl path] MD5], nil]];
  NSLog(@"creating directory: %@", workDir);
  if (![fileManager createDirectoryAtURL:workDir withIntermediateDirectories:YES attributes:nil error:&error]) {
    NSString *msg = [NSString stringWithFormat:@"Error occurred while trying to create directory: %@", error];
    NSAssert(NO, msg);
  }
  
  // copy rar file into work dir
  NSURL *tmpFile = [NSURL fileURLWithPathComponents:
                    [NSArray arrayWithObjects:
                     [workDir path], [fileUrl lastPathComponent], nil]];
  if (![fileManager copyItemAtURL:fileUrl toURL:tmpFile error:&error]) {
    NSString *msg = [NSString stringWithFormat:@"Error occurred while trying to copy file: %@", error];
    NSAssert(NO, msg);
  }
  
  // prepare unrar task
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/usr/local/bin/unrar"];
	[task setCurrentDirectoryPath:[workDir path]];
	NSArray *args = [NSArray arrayWithObjects:@"e", @"-o+", [tmpFile lastPathComponent], nil];
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
  // TODO a status # > 0 suggests a problem, what do we do?
	NSLog(@"unrar ended with status %i & output:\n%@", status, output);
	[output release];
  
  // remove temp file
  if (![fileManager removeItemAtURL:tmpFile error:&error]) {
    NSString *msg = [NSString stringWithFormat:@"Unable to delete temp file: %@", error];
    NSAssert(NO, msg);
  }
  
  // return output path
  return workDir;
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
