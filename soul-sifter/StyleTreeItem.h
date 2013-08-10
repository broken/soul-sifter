//
//  StyleTreeItem.h
//  soul-sifter
//
//  Created by Robby Neale on 12/16/12.
//
//

#import <Foundation/Foundation.h>

#include "Style.h"

@interface StyleTreeItem : NSObject {
@private
    dogatech::soulsifter::Style *style;
}

@property (readonly) StyleTreeItem *parent;
@property (readonly) NSString *name;
@property (readonly) NSMutableArray *children;
@property (readonly) dogatech::soulsifter::Style *style;

- (void)dealloc;

- (id)initWithStyle:(dogatech::soulsifter::Style *)style;
- (id)initWithStyle:(dogatech::soulsifter::Style *)style andParent:(StyleTreeItem *)parent;

@end
