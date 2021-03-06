//
//  StylesTreeDataSource.m
//  soul-sifter
//
//  Created by Robby Neale on 12/16/12.
//
//

#import "StylesTreeDataSource.h"

#include "Style.h"
#include "StyleTreeItem.h"

@implementation StylesTreeDataSource

# pragma mark initialization

- (id)init {
	NSLog(@"stylesTreeDataSource.init");
	if (![super init]) {
		return nil;
	}
    
    styleItems = [[NSMutableArray alloc] init];
    vector<dogatech::soulsifter::Style*>* styles;
    dogatech::soulsifter::Style::findAllSortedByName(&styles);
    for (vector<dogatech::soulsifter::Style*>::iterator it = styles->begin(); it != styles->end(); ++it) {
        const vector<dogatech::soulsifter::Style*> parents = (*it)->getParents();
        if (parents.empty()) {
            StyleTreeItem *styleItem = [[StyleTreeItem alloc] initWithStyle:*it];
            [styleItems addObject:styleItem];
        }
    }
    // do not clear styles since they are being used in the style items
    
	return self;
}

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
	NSLog(@"numberOfChildrenOfItem");
    if (item) {
        return [[(StyleTreeItem *)item children] count];
    } else {
        return [styleItems count];
    }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    NSLog(@"isItemExpandable");
    return [self outlineView:outlineView numberOfChildrenOfItem:item] > 0;
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item {
    NSLog(@"child:ofItem");
    //return [[(StyleTreeItem *)item children] objectAtIndex:index];
    if (item) {
        return [[(StyleTreeItem *)item children] objectAtIndex:index];
    } else {
        return [styleItems objectAtIndex:index];
    }
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    NSString *str = [(StyleTreeItem *)item name];
    return str;
}

@end
