//
//  VGLayer.c
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#include "VGLayerInternal.h"
#include "VGContext.h"
#include <stdlib.h>
#include <stdio.h>

#pragma mark - Class Methods

static void _layerInit(void *memory) {
    VGLayerRef layer = memory;
    vec_init(&layer->children);
    layer->opacity = 1;
}

static void _layerDraw(VGLayerRef layer) {
    if (layer->hidden || layer->opacity == 0) {
        return;
    }

    VGContextRef ctx = VGGetCurrentContext();
    
    VGContextBeginPath(ctx);
    VGRect frame = VGLayerGetFrame(layer);
    float borderRadius = layer->borderRadius;
    if (borderRadius > 0) {
        VGContextRoundedRect(ctx, frame, borderRadius, 0.5f);
    } else {
        VGContextRect(ctx, frame);
    }
    
    if (layer->borderColor.alpha > 0) {
        // has border color
        VGContextSetStrokeColor(ctx, layer->borderColor);
        VGContextStroke(ctx);
    }
    
    VGColor color = layer->backgroundColor;
    VGContextSetFillColor(ctx, color);
    VGContextFill(ctx);
    
    VGLayerRef layerLooper;
    int idx;
    vec_foreach(&layer->children, layerLooper, idx) {
        VGLayerDraw(layerLooper);
    }
}

static bool _layerDispatchEvent(VGLayerRef layer, VGEventRef event) {
    VGLayerRef layerLooper;
    int idx;
    VGPoint position = VGEventGetMousePosition(event);
    vec_foreach(&layer->children, layerLooper, idx) {
        VGRect frame = VGLayerGetFrame(layerLooper);
        if (VGLayerGetFocused(layer) || VGRectContainsPoint(frame, position)) {
            bool result = VGLayerDispatchEvent(layerLooper, event);
            if (result) {
                return result;
            }
        }
    }
    return false;
}

static void _layerSetFrame(VGLayerRef layer, VGRect frame) {
    layer->frame = frame;
}

static void _layerDeallocate(VGObjectRef obj) {
    VGLayerRef layer = (VGLayerRef)obj;
    VGLayerRef layerLooper;
    int idx;
    VGLayerArray children;
    vec_init(&children);
    vec_foreach(&layer->children, layerLooper, idx) {
        vec_push(&children, layerLooper);
    }
    
    vec_foreach(&children, layerLooper, idx) {
        VGLayerRemoveFromSuper(layerLooper);
    }
    
    CALL_SUPER(layer, VGClassRef, deallocate);
}

static struct VGLayerClass kVGLayerClass;

static struct VGLayerClass *kVGLayerClassRef = NULL;

VGLayerClassRef VGLayerGetClass() {
    if (!kVGLayerClassRef) {
        kVGLayerClass.base = kVGBaseClass;
        kVGLayerClass.base.super = &kVGBaseClass;
        kVGLayerClass.base.size = sizeof(struct VGLayer);
        kVGLayerClass.base.deallocate = _layerDeallocate;
        kVGLayerClass.base.init = _layerInit;
        kVGLayerClass.draw = _layerDraw;
        kVGLayerClass.setFrame = _layerSetFrame;
        kVGLayerClass.dispatch = _layerDispatchEvent;
        kVGLayerClassRef = &kVGLayerClass;
    }
    return kVGLayerClassRef;
}

static VGLayerRef kRootLayer = NULL;

VGLayerRef VGLayerCreate(void) {
    VGLayerRef layer = (VGLayerRef)VGObjectCreate((VGClassRef)VGLayerGetClass());
    if (!kRootLayer) {
        VGRetain(layer);
        kRootLayer = layer;
    }
    return layer;
}

VGLayerRef VGLayerGetRoot(void) {
    return kRootLayer;
}

#pragma mark - modify layer
VGRect VGLayerGetFrame(VGLayerRef layer) {
    VGRect frame = layer->frame;
    VGLayerRef looper = layer->parent;
    while (looper) {
        VGRect f = looper->frame;
        frame.origin.x += f.origin.x;
        frame.origin.y += f.origin.y;
        looper = looper->parent;
    }
    return frame;
}

void VGLayerSetFrame(VGLayerRef layer, VGRect frame) {
    VGLayerSetFrameFunc func = METHOD(VGLayerClassRef, layer, setFrame);
    if (!func) {
        func = _layerSetFrame;
    }
    func(layer, frame);
}

void VGLayerSetBackgroundColor(VGLayerRef layer, VGColor color) {
    layer->backgroundColor = color;
}

void VGLayerSetBorderRadius(VGLayerRef layer, float radius) {
    layer->borderRadius = radius;
}
float VGLayerGetBorderRadius(VGLayerRef layer) {
    return layer->borderRadius;
}

void VGLayerSetFocused(VGLayerRef layer, bool focused) {
    layer->focused = focused;
}
bool VGLayerGetFocused(VGLayerRef layer) {
    return layer->focused;
}


void VGLayerSetBorderColor(VGLayerRef layer, VGColor borderColor) {
    layer->borderColor = borderColor;
}
VGColor VGLayerGetBorderColor(VGLayerRef layer) {
    return layer->borderColor;
}

void VGLayerSetHidden(VGLayerRef layer, bool hidden) {
    layer->hidden = hidden;
}
bool VGLayerIsHidden(VGLayerRef layer) {
    return layer->hidden;
}

void VGLayerSetOpacity(VGLayerRef layer, float alpha) {
    layer->opacity = CLAMP(alpha, 0, 1);
}
float VGLayerGetOpacity(VGLayerRef layer) {
    return layer->opacity;
}

#pragma mark - render

void VGLayerDraw(VGLayerRef layer) {
    VGLayerDrawFunc func = METHOD(VGLayerClassRef, layer, draw);
    if (!func) {
        func = _layerDraw;
    }
    func(layer);
}

#pragma mark - Hierarchy
void VGLayerAddSubLayer(VGLayerRef layer, VGLayerRef subLayer) {
    if(subLayer->parent == layer) {
        // do nothing
    } else {
        VGRetain(subLayer);
        
        VGLayerRemoveFromSuper(subLayer);
        
        vec_push(&layer->children, subLayer);
        subLayer->parent = layer;
    }
}

void VGLayerRemoveFromSuper(VGLayerRef layer) {
    VGLayerRef parent = layer->parent;
    if (parent) {
        vec_remove(&parent->children, layer);
        layer->parent = NULL;
        VGRelease(layer);
    }
}

#pragma mark - event
bool VGLayerDispatchEvent(VGLayerRef layer, VGEventRef event) {
    VGLayerDispatchEventFunc func = METHOD(VGLayerClassRef, layer, dispatch);
    if (!func) {
        func = _layerDispatchEvent;
    }
    return func(layer, event);
}
