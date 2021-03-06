//
//  ACRQuickReplyMultilineView
//  ACRQuickReplyMultilineView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRTextView.h"
#import "ACRButton.h"

@interface ACRQuickReplyMultilineView:UIView
@property (strong, nonatomic) IBOutlet UIView *contentView;
@property (weak, nonatomic) IBOutlet ACRTextView *textView;
@property (weak, nonatomic) IBOutlet UIView *spacing;
@property (weak, nonatomic) IBOutlet ACRButton *button;

@end
