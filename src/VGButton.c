//
//  VGButton.c
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#include "VGButton.h"
#include "VGLabel.h"
#include "VGLayerInternal.h"
#include "VGFont.h"
#include "VGContextInternal.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

struct VGButton {
    struct VGLayer base;
    VGLabelRef label;
    VGButtonClickCallback callback;
    const void *userData;
    int icon;
};

static struct VGLayerClass kVGButtonClass;

static struct VGLayerClass *kVGButtonClassRef = NULL;

static void _buttonInit(void *memory) {
    VGLabelRef button = memory;
    CALL_SUPER(button, VGClassRef, init);
    VGLayerSetBackgroundColor(memory, VGColorMake(55 / 255.0f, 140 / 255.0f, 247 / 255.0f, 1));
}

static void _buttonDraw(VGLayerRef layer) {
    VGButtonRef button = (VGButtonRef)layer;
    CALL_SUPER(layer, VGLayerClassRef, draw);
    VGContextRef ctx = VGGetCurrentContext();
    VGRect frame = VGLayerGetFrame(layer);
    if (button->icon) {
        float x = frame.origin.x;
        float y = frame.origin.y;
        float h = frame.size.height;
        float w = frame.size.width;
        VGContextDrawIconAt(ctx, button->icon, VGPointMake(x + w * 0.5f, y + h * 0.5f), h, kVGColorBlack);
    }
//    
//    NVGpaint bg;
//    char icon[8];
//    float cornerRadius = 4.0f;
//    float tw = 0, iw = 0;
//    
//    bg = nvgLinearGradient(vg, x,y,x,y+h, nvgRGBA(255,255,255,isBlack(col)?16:32), nvgRGBA(0,0,0,isBlack(col)?16:32));
//    nvgBeginPath(vg);
//    nvgRoundedRect(vg, x+1,y+1, w-2,h-2, cornerRadius-1);
//    if (!isBlack(col)) {
//        nvgFillColor(vg, col);
//        nvgFill(vg);
//    }
//    nvgFillPaint(vg, bg);
//    nvgFill(vg);
//    
//    nvgBeginPath(vg);
//    nvgRoundedRect(vg, x+0.5f,y+0.5f, w-1,h-1, cornerRadius-0.5f);
//    nvgStrokeColor(vg, nvgRGBA(0,0,0,48));
//    nvgStroke(vg);
//    
//    nvgFontSize(vg, 20.0f);
//    nvgFontFace(vg, "sans-bold");
//    tw = nvgTextBounds(vg, 0,0, text, NULL, NULL);
//    if (preicon != 0) {
//        nvgFontSize(vg, h*1.3f);
//        nvgFontFace(vg, "icons");
//        iw = nvgTextBounds(vg, 0,0, cpToUTF8(preicon,icon), NULL, NULL);
//        iw += h*0.15f;
//    }
//    
//    if (preicon != 0) {
//        nvgFontSize(vg, h*1.3f);
//        nvgFontFace(vg, "icons");
//        nvgFillColor(vg, nvgRGBA(255,255,255,96));
//        nvgTextAlign(vg,NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
//        nvgText(vg, x+w*0.5f-tw*0.5f-iw*0.75f, y+h*0.5f, cpToUTF8(preicon,icon), NULL);
//    }
//    
//    nvgFontSize(vg, 20.0f);
//    nvgFontFace(vg, "sans-bold");
//    nvgTextAlign(vg,NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
//    nvgFillColor(vg, nvgRGBA(0,0,0,160));
//    nvgText(vg, x+w*0.5f-tw*0.5f+iw*0.25f,y+h*0.5f-1,text, NULL);
//    nvgFillColor(vg, nvgRGBA(255,255,255,160));
//    nvgText(vg, x+w*0.5f-tw*0.5f+iw*0.25f,y+h*0.5f,text, NULL);
}

static bool _buttonDispatch(VGLayerRef layer, VGEventRef event) {
    int button = VGEventGetButton(event);
    int action = VGEventGetAction(event);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // click event
        VGButtonRef button = (VGButtonRef)layer;
        if(button->callback) {
            button->callback(button, button->userData);
        }
        return true;
    }
    return false;
}

VGLayerClassRef VGButtonGetClass() {
    if (!kVGButtonClassRef) {
        kVGButtonClass.base = kVGBaseClass;
        kVGButtonClass.base.super = (VGClassRef)VGLayerGetClass();
        kVGButtonClass.base.size = sizeof(struct VGButton);
        kVGButtonClass.base.init = _buttonInit;
        kVGButtonClass.draw = _buttonDraw;
        kVGButtonClass.dispatch = _buttonDispatch;
        kVGButtonClassRef = &kVGButtonClass;
    }
    return kVGButtonClassRef;
}

VGButtonRef VGButtonCreate(void) {
    VGButtonRef button = (VGButtonRef)VGObjectCreate((VGClassRef)VGButtonGetClass());
    return button;
}

VGLabelRef VGButtonGetLabel(VGButtonRef button) {
    if (!button->label) {
        button->label = VGLabelCreate();
        VGLayerAddSubLayer((VGLayerRef)button, (VGLayerRef)button->label);
    }
    return button->label;
}

void VGButtonSetIcon(VGButtonRef button, int icon) {
    button->icon = icon;
}

int VGButtonGetIcon(VGButtonRef button) {
    return button->icon;
}

void VGButtonSetClickCallback(VGButtonRef button, VGButtonClickCallback callback, const void *userData) {
    button->callback = callback;
    button->userData = userData;
}
