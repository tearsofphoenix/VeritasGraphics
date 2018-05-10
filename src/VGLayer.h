//
//  VGLayer.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGLayer_h
#define VGLayer_h

#include "VGDefine.h"
#include "VGGeometry.h"
#include "VGTypes.h"
#include "VGObject.h"
#include "VGColor.h"

VG_BEGIN


typedef struct VGLayer *VGLayerRef;

extern VGLayerRef VGLayerCreate(void);

extern void VGLayerSetFrame(VGLayerRef layer, VGRect frame);
extern VGRect VGLayerGetFrame(VGLayerRef layer);

extern void VGLayerDraw(VGLayerRef layer);

extern void VGLayerSetBackgroundColor(VGLayerRef layer, VGColor color);

extern void VGLayerSetBorderRadius(VGLayerRef layer, float radius);
extern float VGLayerGetBorderRadius(VGLayerRef layer);

extern void VGLayerSetBorderColor(VGLayerRef layer, VGColor borderColor);
extern VGColor VGLayerGetBorderColor(VGLayerRef layer);

extern void VGLayerSetFocused(VGLayerRef layer, bool focused);
extern bool VGLayerGetFocused(VGLayerRef layer);

extern void VGLayerSetHidden(VGLayerRef layer, bool hidden);
extern bool VGLayerIsHidden(VGLayerRef layer);

extern void VGLayerSetOpacity(VGLayerRef layer, float alpha);
extern float VGLayerGetOpacity(VGLayerRef layer);

// hierarchy
extern void VGLayerAddSubLayer(VGLayerRef layer, VGLayerRef subLayer);

extern void VGLayerRemoveFromSuper(VGLayerRef layer);

extern VGLayerRef VGLayerGetRoot(void);

VG_END

#endif /* VGLayer_h */
