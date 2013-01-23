//
//  StyleTreeItem.m
//  soul-sifter
//
//  Created by Robby Neale on 12/16/12.
//
//

#import "StyleTreeItem.h"

@implementation StyleTreeItem

# pragma mark initialization

- (id)initWithStyle:(soulsifter::Style *)ssStyle {
	NSLog(@"initWithStyle");
	if (![super init]) {
		return nil;
	}
    style = ssStyle;
    parent = nil;
    name = [NSString stringWithUTF8String:style->getName().c_str()];
    [name retain];
    children = [[NSMutableArray alloc] init];
    const vector<soulsifter::Style*> kids = style->getChildren();
    for (vector<soulsifter::Style*>::const_iterator it = kids.begin(); it != kids.end(); ++it) {
        [children addObject:[[StyleTreeItem alloc] initWithStyle:*it andParent:self]];
    }
    return self;
}


- (id)initWithStyle:(soulsifter::Style *)ssStyle andParent:(StyleTreeItem *)itemParent {
	NSLog(@"initWithStyle:andParent");
    [self initWithStyle:ssStyle];
    parent = itemParent;
    return self;
}

# pragma mark accessors

@synthesize parent;
@synthesize children;
@synthesize name;
@synthesize style;

@end
