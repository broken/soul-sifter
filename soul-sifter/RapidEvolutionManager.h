//
//  RapidEvolutionManager.h
//  soul-sifter
//
//  Created by Robby Neale on 6/25/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Song;

@interface RapidEvolutionManager : NSObject

+ (RapidEvolutionManager *)default;

- (void)writeSongToXml:(Song *)song;
- (void)flushXml;

@end
