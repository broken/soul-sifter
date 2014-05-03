//
//  ImageViewWithFilepath.m
//  soul-sifter
//
//  Created by Robby Neale on 1/10/14.
//
//

#import "ImageViewWithFilepath.h"

@implementation ImageViewWithFilepath

- (void)setImage:(NSImage *)image
{
  [image setName:[[mImagename lastPathComponent] stringByDeletingPathExtension]];
  [super setImage:image];
}

- (BOOL)performDragOperation:(id )sender
{
  BOOL dragSucceeded = [super performDragOperation:sender];
  if (dragSucceeded) {
    NSString *filenamesXML = [[sender draggingPasteboard] stringForType:NSFilenamesPboardType];
    if (filenamesXML) {
      NSArray *filenames = [NSPropertyListSerialization
                            propertyListFromData:[filenamesXML dataUsingEncoding:NSUTF8StringEncoding]
                            mutabilityOption:NSPropertyListImmutable
                            format:nil
                            errorDescription:nil];
      if ([filenames count] >= 1) {
        mImagename = [filenames objectAtIndex:0];
      } else {
        mImagename = nil;
      }
    }
  }
  return dragSucceeded;
}

@end