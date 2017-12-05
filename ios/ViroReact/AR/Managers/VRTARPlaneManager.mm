//
//  VRTARPlaneManager.mm
//  ViroReact
//
//  Created by Andy Chu on 6/15/17.
//  Copyright © 2017 Viro Media. All rights reserved.
//

#import "VRTARPlaneManager.h"
#import "VRTARPlane.h"
#import "VRTNodeContainerShadowView.h"

@implementation VRTARPlaneManager

RCT_EXPORT_MODULE()

RCT_EXPORT_VIEW_PROPERTY(anchorId, NSString)
RCT_EXPORT_VIEW_PROPERTY(minHeight, float)
RCT_EXPORT_VIEW_PROPERTY(minWidth, float)
RCT_EXPORT_VIEW_PROPERTY(pauseUpdates, BOOL)
RCT_EXPORT_VIEW_PROPERTY(visible, BOOL)
RCT_EXPORT_VIEW_PROPERTY(onHoverViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onClickViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onFuseViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onDragViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(timeToFuse, float)
RCT_EXPORT_VIEW_PROPERTY(canHover, BOOL)
RCT_EXPORT_VIEW_PROPERTY(canClick, BOOL)
RCT_EXPORT_VIEW_PROPERTY(canFuse, BOOL)
RCT_EXPORT_VIEW_PROPERTY(canDrag, BOOL)
RCT_EXPORT_VIEW_PROPERTY(onPinchViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onRotateViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(canPinch, BOOL)
RCT_EXPORT_VIEW_PROPERTY(canRotate, BOOL)
RCT_EXPORT_VIEW_PROPERTY(opacity, float)
RCT_EXPORT_VIEW_PROPERTY(onCollisionViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(canCollide, BOOL)
RCT_EXPORT_VIEW_PROPERTY(viroTag, NSString)
RCT_EXPORT_VIEW_PROPERTY(onAnchorFoundViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onAnchorUpdatedViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onAnchorRemovedViro, RCTDirectEventBlock)
RCT_EXPORT_VIEW_PROPERTY(ignoreEventHandling, BOOL)
RCT_EXPORT_VIEW_PROPERTY(dragType, NSString)

- (VRTNodeContainerShadowView *)shadowView
{
    return [VRTNodeContainerShadowView new];
}

-(VRTARPlane *)view
{
    return [[VRTARPlane alloc] initWithBridge:self.bridge];
}

@end