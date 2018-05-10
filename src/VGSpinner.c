//
//  VGSpinner.c
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#include "VGSpinner.h"
#include "VGLayerInternal.h"

#include <math.h>

struct VGSpinner {
    struct VGLayer base;
    VGColor startColor;
    VGColor endColor;
    float t;
};

static void _spinnerInit(void *memory) {
    VGSpinnerRef spinner = memory;
    CALL_SUPER(spinner, VGClassRef, init);
    
    spinner->startColor = VGColorMake(0, 0, 0, 0);
    spinner->endColor = VGColorMake(0, 0, 0, 0.5);
}

static void _spinnerDraw(VGLayerRef layer) {
    CALL_SUPER(layer, VGLayerClassRef, draw);
    VGSpinnerRef spinner = (VGSpinnerRef)layer;
    VGRect frame = VGLayerGetFrame(layer);
    float t = spinner->t;
    VGContextRef ctx = VGGetCurrentContext();
    float a0 = 0.0f + t * 6;
    float a1 = NVG_PI + t * 6;
    float r = frame.size.width / 2.0f;
    float cx = VGRectMidX(frame);
    float cy = VGRectMidY(frame);
    float r0 = r;
    float r1 = r * 0.75f;
    float ax,ay, bx,by;
    
    VGContextSaveState(ctx);
    
    VGContextBeginPath(ctx);
    
    VGContextArc(ctx, cx, cy, r0, a0, a1, NVG_CW);
    VGContextArc(ctx, cx, cy, r1, a1, a0, NVG_CCW);
    VGContextCloseSubPath(ctx);
    
    ax = cx + cosf(a0) * (r0+r1)*0.5f;
    ay = cy + sinf(a0) * (r0+r1)*0.5f;
    bx = cx + cosf(a1) * (r0+r1)*0.5f;
    by = cy + sinf(a1) * (r0+r1)*0.5f;
    
    VGGradientRef gradient = VGGradientCreate(spinner->startColor, spinner->endColor);
    VGContextDrawLinearGradient(ctx, gradient, VGPointMake(ax, ay), VGPointMake(bx, by));
    
    VGContextFill(ctx);
    VGRelease(gradient);
    
    VGContextRestoreState(ctx);
}

static struct VGLayerClass kVGSpinnerClass;

static VGLayerClassRef kVGSpinnerClassRef = NULL;

static VGClassRef VGSpinnerGetClass() {
    if (!kVGSpinnerClassRef) {
        VGLayerClassRef layerClass = VGLayerGetClass();
        kVGSpinnerClass.base = layerClass->base;
        kVGSpinnerClass.base.size = sizeof(struct VGSpinner);
        kVGSpinnerClass.base.super = (VGClassRef)layerClass;
        kVGSpinnerClass.base.init = _spinnerInit;
        kVGSpinnerClass.draw = _spinnerDraw;
        
        kVGSpinnerClassRef = &kVGSpinnerClass;
    }
    return (VGClassRef)kVGSpinnerClassRef;
}

VGSpinnerRef VGSpinnerCreate(void) {
    VGSpinnerRef spinner = (VGSpinnerRef)VGObjectCreate(VGSpinnerGetClass());
    return spinner;
}

void VGSpinnerSetT(VGSpinnerRef spinner, float t) {
    spinner->t = t;
}

void VGSpinnerSetStartColor(VGSpinnerRef spinner, VGColor color) {
    spinner->startColor = color;
}
VGColor VGSpinnerGetStartColor(VGSpinnerRef spinner) {
    return spinner->startColor;
}

void VGSpinnerSetEndColor(VGSpinnerRef spinner, VGColor color) {
    spinner->endColor = color;
}
VGColor VGSpinnerGetEndColor(VGSpinnerRef spinner) {
    return spinner->endColor;
}
