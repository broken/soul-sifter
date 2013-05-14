//
//  NSOutlineView+DTSelection.h
//  soul-sifter
//
//  Created by Robby Neale on 4/15/13.
//
//

#import <Foundation/Foundation.h>

@interface NSOutlineView (DTSelection)

- (void)expandParentsOfItem:(id)item;
- (void)selectItem:(id)item;

@end
