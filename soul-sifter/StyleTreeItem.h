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
    soulsifter::Style *style;
}

@property (readonly) StyleTreeItem *parent;
@property (readonly) NSString *name;
@property (readonly) NSMutableArray *children;
@property (readonly) soulsifter::Style *style;

- (void)dealloc;

- (id)initWithStyle:(soulsifter::Style *)style;
- (id)initWithStyle:(soulsifter::Style *)style andParent:(StyleTreeItem *)parent;

@end
