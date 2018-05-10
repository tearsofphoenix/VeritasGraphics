//
//  VGContext.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGContext_h
#define VGContext_h

#include "VGDefine.h"

VG_BEGIN

#include "nanovg.h"
#include "VGGeometry.h"
#include "VGTypes.h"
#include "VGGradient.h"

typedef struct VGContext *VGContextRef;

extern VGContextRef VGContextCreate(NVGcontext *ctx);

extern VGContextRef VGGetCurrentContext(void);

extern void VGContextSetFillColor(VGContextRef ctx, VGColor color);

extern void VGContextFill(VGContextRef ctx);

extern void VGContextSetStrokeColor(VGContextRef ctx, VGColor color);

extern void VGContextStroke(VGContextRef ctx);

extern void VGContextBeginPath(VGContextRef ctx);

extern void VGContextCloseSubPath(VGContextRef ctx);

extern void VGContextRect(VGContextRef ctx, VGRect rect);

extern void VGContextSetFont(VGContextRef ctx, const char *fontName);

extern void VGContextSetFontSize(VGContextRef ctx, float size);

extern void VGContextDrawText(VGContextRef ctx, float x, float y, const char *text);

extern void VGContextSetTextAlign(VGContextRef ctx, enum NVGalign align);

extern void VGContextRoundedRect(VGContextRef ctx, VGRect rect, float radius, float offset);

extern void VGContextCircle(VGContextRef ctx, float cx, float cy, float radius);

extern void VGContextArc(VGContextRef ctx, float cx, float cy, float radius, float startAngle, float endAngle, int clockWise);

extern void VGContextSaveState(VGContextRef ctx);

extern void VGContextRestoreState(VGContextRef ctx);

extern void VGContextDrawLinearGradient(VGContextRef ctx, VGGradientRef gradient, VGPoint startPoint, VGPoint endPoint);

extern void VGContextDrawBoxlGradient(VGContextRef ctx, VGGradientRef gradient, VGRect rect, float radius, float f);

extern float VGContextMeasureText(VGContextRef ctx, const char *text);

VG_END

#endif /* VGContext_h */
