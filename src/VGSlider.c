//
//  VGSlider.c
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#include "VGSlider.h"
#include "VGLayerInternal.h"
#include "VGContext.h"

struct VGSlider {
    struct VGLayer base;
    float value;
};

static void _sliderDraw(VGLayerRef layer) {
    VGSliderRef slider = (VGSliderRef)layer;
    VGRect frame = VGLayerGetFrame(layer);
    float y = frame.origin.y;
    float h = frame.size.height;
    
    NVGpaint bg, knob;
    float cy = y+(int)(h*0.5f);
    float kr = (int)(h*0.25f);
    
    VGContextRef ctx = VGGetCurrentContext();
    VGContextSaveState(ctx);
    
    // Slot
    VGGradientRef gradient = VGGradientCreate(VGColorMake(0, 0, 0, 32.0f / 255.0f), VGColorMake(0, 0, 0, 0.5));
    VGContextDrawBoxlGradient(ctx, gradient, frame, 2, 2);
    VGContextRoundedRect(ctx, frame, 4, 2);
    VGContextFill(ctx);
    
    // Knob Shadow
    
//    bg = nvgRadialGradient(vg, x+(int)(pos*w),cy+1, kr-3,kr+3, nvgRGBA(0,0,0,64), nvgRGBA(0,0,0,0));
//    nvgBeginPath(vg);
//    nvgRect(vg, x+(int)(pos*w)-kr-5,cy-kr-5,kr*2+5+5,kr*2+5+5+3);
//    nvgCircle(vg, x+(int)(pos*w),cy, kr);
//    nvgPathWinding(vg, NVG_HOLE);
//    nvgFillPaint(vg, bg);
//    nvgFill(vg);
//    
//    // Knob
//    knob = nvgLinearGradient(vg, x,cy-kr,x,cy+kr, nvgRGBA(255,255,255,16), nvgRGBA(0,0,0,16));
//    nvgBeginPath(vg);
//    nvgCircle(vg, x+(int)(pos*w),cy, kr-1);
//    nvgFillColor(vg, nvgRGBA(40,43,48,255));
//    nvgFill(vg);
//    nvgFillPaint(vg, knob);
//    nvgFill(vg);
//    
//    nvgBeginPath(vg);
//    nvgCircle(vg, x+(int)(pos*w),cy, kr-0.5f);
//    nvgStrokeColor(vg, nvgRGBA(0,0,0,92));
//    nvgStroke(vg);
//    
//    nvgRestore(vg);
}

static struct VGLayerClass kVGSliderClass;
static VGLayerClassRef kVGSliderClassRef = NULL;

static VGClassRef VGSliderGetClass(void) {
    if (!kVGSliderClassRef) {
        VGLayerClassRef layerClass = VGLayerGetClass();
        kVGSliderClass.base = layerClass->base;
        kVGSliderClass.base.size = sizeof(struct VGSlider);
        kVGSliderClass.base.super = layerClass;
        kVGSliderClass.draw = _sliderDraw;
        kVGSliderClassRef = &kVGSliderClass;
    }
    return (VGClassRef)kVGSliderClassRef;
}

VGSliderRef VGSliderCreate(void) {
    VGSliderRef slider = (VGSliderRef)VGObjectCreate(VGSliderGetClass());
    return slider;
}

void VGSliderSetValue(VGSliderRef slider, float value) {
    slider->value = value;
}

float VGSliderGetValue(VGSliderRef slider) {
    return slider->value;
}
