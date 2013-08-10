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

- (id)initWithStyle:(dogatech::soulsifter::Style *)ssStyle {
	NSLog(@"initWithStyle");
	if (![super init]) {
		return nil;
	}
    style = ssStyle;
    parent = nil;
    name = [NSString stringWithUTF8String:style->getName().c_str()];
    [name retain];
    children = [[NSMutableArray alloc] init];
    const vector<dogatech::soulsifter::Style*> kids = style->getChildren();
    for (vector<dogatech::soulsifter::Style*>::const_iterator it = kids.begin(); it != kids.end(); ++it) {
        [children addObject:[[StyleTreeItem alloc] initWithStyle:*it andParent:self]];
    }
    return self;
}


- (id)initWithStyle:(dogatech::soulsifter::Style *)ssStyle andParent:(StyleTreeItem *)itemParent {
	NSLog(@"initWithStyle:andParent");
    [self initWithStyle:ssStyle];
    parent = itemParent;
    return self;
}

- (void)dealloc {
    delete style;
    style = NULL;
    
    [super dealloc];
}

# pragma mark accessors

@synthesize parent;
@synthesize children;
@synthesize name;
@synthesize style;

@end
