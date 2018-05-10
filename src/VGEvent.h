//
//  VGEvent.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGEvent_h
#define VGEvent_h

#include "VGDefine.h"
#include "VGGeometry.h"

VG_BEGIN

typedef enum {
    kVGEventKey,
    kVGEventMouse,
    kVGEventText
} VGEventType;

typedef struct VGEvent *VGEventRef;

extern void VGTextEventCallback(void *window, unsigned int codepoint);

extern void VGKeyEventCallback(void *window, int key, int scancode, int action, int mods);

extern void VGMouseEventCallback(void* window, int button, int action, int mods);

extern VGPoint VGEventGetMousePosition(VGEventRef event);

extern VGEventType VGEventGetType(VGEventRef event);

extern unsigned int VGEventGetCodePoint(VGEventRef event);

extern int VGEventGetKey(VGEventRef event);

extern int VGEventGetAction(VGEventRef event);

extern int VGEventGetButton(VGEventRef event);

extern int VGEventGetScancode(VGEventRef event);

extern int VGEventGetMods(VGEventRef event);

VG_END

#endif /* VGEvent_h */
