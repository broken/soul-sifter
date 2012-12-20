//
//  StylesTreeDataSource.h
//  soul-sifter
//
//  Created by Robby Neale on 12/16/12.
//
//

#import <Cocoa/Cocoa.h>

@interface StylesTreeDataSource : NSObject <NSOutlineViewDataSource> {
@private
    NSMutableArray *styleItems;
}

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item;
- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item;
- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item;
- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item;

@end
