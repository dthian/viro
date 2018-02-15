//
//  VROARSession.h
//  ViroKit
//
//  Created by Raj Advani on 6/6/17.
//  Copyright © 2017 Viro Media. All rights reserved.
//

#ifndef VROARSession_h
#define VROARSession_h

#include <memory>
#include <set>
#include "VROLog.h"
#include "VROMatrix4f.h"

class VROARAnchor;
class VROARFrame;
class VROTexture;
class VROViewport;
class VROScene;
class VROARNode;
class VRONode;
class VROARSessionDelegate;
class VROARImageTarget;
enum class VROCameraOrientation; //defined in VROCameraTexture.h

/*
 Determines if the AR session tracks orientation only, or
 tracks position and orientation.
 */
enum class VROTrackingType {
    DOF3,
    DOF6
};

/*
 The types of objects the AR session should scan each frame 
 to detect. A VROARAnchor is created for each detected object.
 */
enum class VROAnchorDetection {
    None,
    PlanesHorizontal,
    PlanesVertical
};

/*
 The world alignment chosen at the start of the AR Session.
 */
enum class VROWorldAlignment {
    Gravity,
    GravityAndHeading,
    Camera
};

/*
 The implementation of image tracking to use.
 */
enum class VROImageTrackingImpl {
    ARKit,
    Viro // not available for devs to use yet.
};

/*
 Manages the device camera and motion tracking for AR.
 */
class VROARSession {
public:
    
    VROARSession(VROTrackingType trackingType, VROWorldAlignment worldAlignment) :
        _trackingType(trackingType),
        _worldAlignment(worldAlignment),
        _imageTrackingImpl(VROImageTrackingImpl::ARKit) {}
    virtual ~VROARSession() {}
    
    VROTrackingType getTrackingType() const {
        return _trackingType;
    }

    VROWorldAlignment getWorldAlignment() const {
        return _worldAlignment;
    }
    
    VROImageTrackingImpl getImageTrackingImpl() const {
        return _imageTrackingImpl;
    }
    
    /*
     The scene associated with this session.
     */
    const std::shared_ptr<VROScene> getScene() const {
        return _scene;
    }
    virtual void setScene(std::shared_ptr<VROScene> scene) {
        _scene = scene;
    }
    
    /*
     The delegate set by the application to respond to events from the
     AR session.
     */
    std::shared_ptr<VROARSessionDelegate> getDelegate() {
        return _delegate.lock();
    }
    virtual void setDelegate(std::shared_ptr<VROARSessionDelegate> delegate) {
        _delegate = delegate;
    }
    
    /*
     Start the session. The session cannot be started until its
     scene, viewport, and orientation have been set.
     */
    virtual void run() = 0;
    
    /*
     Pause the session. No new frames will be created.
     */
    virtual void pause() = 0;

    /*
     Resets the VROARSession depending on the given boolean flags. If no flags
     are set to true, then nothing will happen.
     */
    virtual void resetSession(bool resetTracking, bool removeAnchors) = 0;

    /*
     Returns true if at least one frame has been generated.
     */
    virtual bool isReady() const = 0;
    
    /*
     Set what anchors will be auto-detected by the AR session.
     */
    virtual void setAnchorDetection(std::set<VROAnchorDetection> types) = 0;
    
    /*
     Adds an image target that should be tracked by this session.
     */
    virtual void addARImageTarget(std::shared_ptr<VROARImageTarget> target) = 0;

    /*
     Removes an image target that should no longer be tracked by this session and the
     corresponding anchor that matched with the target. If the image target has not
     been found yet, then the given anchor should be nullptr
     */
    virtual void removeARImageTarget(std::shared_ptr<VROARImageTarget> target) = 0;
    
    /*
     Add or remove anchors from the session. These methods are used for
     placing anchors that are *not* auto-detected. The AR session will
     not keep these anchors up to date; that is the responsibility of the
     system that added the anchor.
     */
    virtual void addAnchor(std::shared_ptr<VROARAnchor> anchor) = 0;
    virtual void removeAnchor(std::shared_ptr<VROARAnchor> anchor) = 0;
    
    /*
     Invoke to update the anchor's node with the latest transformation
     data contained in the anchor, alerting delegates in the process.
     */
    virtual void updateAnchor(std::shared_ptr<VROARAnchor> anchor) = 0;
    
    /*
     Invoke each rendering frame. Updates the AR session with the latest
     AR data, and returns this in a VROARFrame. The camera background is
     updated at this point as well.
     */
    virtual std::unique_ptr<VROARFrame> &updateFrame() = 0;
    
    /*
     Get the last frame that was generated via updateFrame().
     */
    virtual std::unique_ptr<VROARFrame> &getLastFrame() = 0;
    
    /*
     Get the background texture for this AR session. The contents of this
     texture are updated after each call to updateFrame().
     */
    virtual std::shared_ptr<VROTexture> getCameraBackgroundTexture() = 0;
    
    /*
     Invoke when the viewport changes. The AR engine may adjust its camera
     background and projection matrices in response to a viewport change.
     */
    virtual void setViewport(VROViewport viewport) = 0;
    
    /*
     Invoke when orientation changes, so the AR engine can make the 
     necessary adjustments.
     */
    virtual void setOrientation(VROCameraOrientation orientation) = 0;

    /*
     Sets AR world origin to the given transform.
     */
    virtual void setWorldOrigin(VROMatrix4f relativeTransform) = 0;
    
private:
    
    VROTrackingType _trackingType;
    VROWorldAlignment _worldAlignment;
    VROImageTrackingImpl _imageTrackingImpl;
    std::shared_ptr<VROScene> _scene;
    std::weak_ptr<VROARSessionDelegate> _delegate;

};

class VROARSessionDelegate {
public:
    
    /*
     Invoked whenever an anchor is detected by the AR session, or when an 
     anchor is manually added to the session via addAnchor(). The application
     can choose to add a VROARNode to associate virtual content with this
     anchor by setting a VROARNode on the anchor.
     */
    virtual void anchorWasDetected(std::shared_ptr<VROARAnchor> anchor) = 0;
    
    /*
     Invoked just before and after the anchor's node's properties are updated
     to match the current state of the anchor.
     */
    virtual void anchorWillUpdate(std::shared_ptr<VROARAnchor> anchor) = 0;
    virtual void anchorDidUpdate(std::shared_ptr<VROARAnchor> anchor) = 0;
    
    /*
     Invoked when an anchor is removed from the AR session, along with its
     corresponding node (now detached from the scene).
     */
    virtual void anchorWasRemoved(std::shared_ptr<VROARAnchor> anchor) = 0;
    
};

#endif /* VROARSession_h */
