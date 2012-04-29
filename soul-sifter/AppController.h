//
//  AppController.h
//  soul-sifter
//
//  Created by Robby Neale on 4/28/12.
//  Copyright (c) 2012 Dogatech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DropBox;
@class TagInfoController;

@interface AppController : NSObject {
@private
    IBOutlet DropBox *dropBox;
    
    TagInfoController *tagInfoController;
}

- (IBAction)showTagInfoWindow:(id)sender;

@end
