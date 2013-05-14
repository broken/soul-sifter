//
//  NSOutlineView+DTSelection.m
//  soul-sifter
//
//  Created by Robby Neale on 4/15/13.
//
//

#import "NSOutlineView+DTSelection.h"

@implementation NSOutlineView (DTSelection)

- (void)expandParentsOfItem:(id)item {
    while (item != nil) {
        id parent = [self parentForItem: item];
        if (![self isExpandable: parent])
            break;
        if (![self isItemExpanded: parent])
            [self expandItem: parent];
        item = parent;
    }
}

- (void)selectItem:(id)item {
    NSInteger itemIndex = [self rowForItem:item];
    if (itemIndex < 0) {
        [self expandParentsOfItem: item];
        itemIndex = [self rowForItem:item];
        if (itemIndex < 0)
            return;
    }
    [self selectRowIndexes: [NSIndexSet indexSetWithIndex: itemIndex] byExtendingSelection: YES];
}

@end
