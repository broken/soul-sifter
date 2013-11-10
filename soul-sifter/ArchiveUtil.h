//
//  ArchiveUtil.h
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#import <Foundation/Foundation.h>

@interface ArchiveUtil : NSObject
{
}
+(void)unzipFile:(NSString *)file toPath:(NSString *)path;
+(NSURL *)unrarFile:(NSURL *)fileUrl;
+(NSURL *)unzipFile:(NSURL *)fileUrl;

@end