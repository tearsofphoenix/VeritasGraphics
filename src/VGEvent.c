//
//  VGEvent.c
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#include "VGEvent.h"
#include "VGObjectInternal.h"
#include "VGLayerInternal.h"
#include <GLFW/glfw3.h>

struct VGEvent {
    struct VGObject base;
    VGPoint mousePosition;
    VGEventType type;
    unsigned int codepoint;
    int key;
    int scancode;
    int action;
    int mods;
    int button;
};

static VGClass kVGEventClass;
static VGClassRef kVGEventClassRef = NULL;

static VGClassRef VGEventGetClass(void) {
    if (!kVGEventClassRef) {
        kVGEventClass = kVGBaseClass;
        kVGEventClass.size = sizeof(struct VGEvent);
        kVGEventClass.super = &kVGBaseClass;
        kVGEventClassRef = &kVGEventClass;
    }
    return kVGEventClassRef;
}

VGEventRef VGEventCreate(VGPoint position,
                         VGEventType type,
                         int action,
                         int mods) {
    VGEventRef event = (VGEventRef)VGObjectCreate(VGEventGetClass());
    event->type = type;
    event->mousePosition = position;
    event->action = action;
    event->mods = mods;
        
    return event;
}

unsigned int VGEventGetCodePoint(VGEventRef event) {
    return event->codepoint;
}

int VGEventGetKey(VGEventRef event) {
    return event->key;
}

int VGEventGetAction(VGEventRef event) {
    return event->action;
}

int VGEventGetButton(VGEventRef event) {
    return event->button;
}

int VGEventGetScancode(VGEventRef event) {
    return event->scancode;
}

int VGEventGetMods(VGEventRef event) {
    return event->mods;
}

VGPoint VGEventGetMousePosition(VGEventRef event) {
    return event->mousePosition;
}

VGEventType VGEventGetType(VGEventRef event) {
    return event->type;
}

void VGTextEventCallback(void *window, unsigned int codepoint) {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    VGEventRef event = VGEventCreate(VGPointMake(x, y), kVGEventText, 0, 0);
    event->codepoint = codepoint;
    VGLayerRef rootLayer = VGLayerGetRoot();
    VGLayerDispatchEvent(rootLayer, event);
    VGRelease(event);
}

void VGKeyEventCallback(void *window, int key, int scancode, int action, int mods) {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    VGEventRef event = VGEventCreate(VGPointMake(x, y), kVGEventKey, action, mods);
    event->key = key;
    event->scancode = scancode;
    VGLayerRef rootLayer = VGLayerGetRoot();
    VGLayerDispatchEvent(rootLayer, event);
    VGRelease(event);
}

void VGMouseEventCallback(void* window, int button, int action, int mods) {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    VGEventRef event = VGEventCreate(VGPointMake(x, y), kVGEventMouse, action, mods);
    event->button = button;
    VGLayerRef rootLayer = VGLayerGetRoot();
    VGLayerDispatchEvent(rootLayer, event);
    VGRelease(event);
}
