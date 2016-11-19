/**
 * Copyright @2016 ViroMedia. All rights reserved.
 */
package com.viromedia.virobridge;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.JavaScriptModule;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;

import java.util.Arrays;
import java.util.List;

import static java.util.Collections.emptyList;

/**
 * ViroReactPackage class containing an array of all ViroViewManagers to be created.
 */
public class ViroReactPackage implements ReactPackage {
    @Override
    public List<NativeModule> createNativeModules(ReactApplicationContext reactContext) {
        return emptyList();
    }

    @Override
    public List<Class<? extends JavaScriptModule>> createJSModules() {
        return emptyList();
    }

    @Override
    public List<ViewManager> createViewManagers(ReactApplicationContext reactContext) {
        return Arrays.<ViewManager>asList(new SceneNavigatorManager(reactContext));
    }
}