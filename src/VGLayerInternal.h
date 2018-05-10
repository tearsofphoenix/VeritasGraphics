//
//  VGLayerInternal.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGLayerInternal_h
#define VGLayerInternal_h

#include "VGLayer.h"
#include "VGTypes.h"
#include "VGObjectInternal.h"
#include "vec.h"
#include "VGEvent.h"

VG_BEGIN
typedef void (* VGLayerDrawFunc)(VGLayerRef layer);
typedef void (* VGLayerSetFrameFunc)(VGLayerRef layer, VGRect frame);
typedef bool (* VGLayerDispatchEventFunc)(VGLayerRef layer, VGEventRef event);
typedef vec_t(VGLayerRef) VGLayerArray;

struct VGLayerClass {
    VGClass base;
    VGLayerSetFrameFunc setFrame;
    VGLayerDrawFunc draw;
    VGLayerDispatchEventFunc dispatch;
};

typedef struct VGLayerClass *VGLayerClassRef;

struct VGLayer {
    struct VGObject base;
    VGLayerRef parent;
    VGLayerArray children;
    VGRect frame;
    VGColor backgroundColor;
    float borderRadius;
    bool focused;
    bool hidden;
    float opacity;
    VGColor borderColor;
};

extern VGLayerClassRef VGLayerGetClass(void);

extern bool VGLayerDispatchEvent(VGLayerRef layer, VGEventRef event);

VG_END

#endif /* VGLayerInternal_h */
