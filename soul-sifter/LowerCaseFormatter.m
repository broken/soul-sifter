//
//  LowerCaseFormatter.m
//  soul-sifter
//
//  Created by Robby Neale on 4/29/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import "LowerCaseFormatter.h"

@implementation LowerCaseFormatter

# pragma mark overrides

- (NSString *)stringForObjectValue:(id)obj {
    if (![obj isKindOfClass:[NSString class]]) {
        return nil;
    }
    return [obj lowercaseString];
}

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string errorDescription:(NSString **)error {
    *obj = string;
    return YES;
}

@end
