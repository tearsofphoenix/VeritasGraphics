//
//  VGLabel.c
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#include "VGLabel.h"
#include "VGLayerInternal.h"
#include "VGFont.h"
#include "VGContext.h"
#include <stdlib.h>
#include <string.h>

struct VGLabel {
    struct VGLayer base;
    const char *title;
    VGFontRef font;
    VGColor textColor;
};

static void _labelInit(void *memory) {
    VGLabelRef label = memory;
    CALL_SUPER(label, VGClassRef, init);

    VGLabelSetFont(label, VGFontGetDefault());
    VGLabelSetTextColor(label, VGColorMake(0, 0, 0, 1));
}

static void _labelDraw(VGLabelRef label) {
    CALL_SUPER(label, VGLayerClassRef, draw);
    
    VGContextRef ctx = VGGetCurrentContext();
    VGFontApply(ctx, label->font);
    
    VGContextSetTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    
    const char *title = VGLabelGetTitle(label);
    if (title) {
        VGContextSetFillColor(ctx, label->textColor);
        
        VGRect frame = VGLayerGetFrame((VGLayerRef)label);
        float x = frame.origin.x;
        float y = frame.origin.y;
        VGContextDrawText(ctx, x, y, title);
    }
}

static void _labelDeallocate(VGLabelRef label) {
    VGRelease(label->font);
    free((void *)label->title);
    CALL_SUPER(label, VGClassRef, deallocate);
}

static struct VGLayerClass kLabelClass;

static struct VGLayerClass *kLabelClassRef = NULL;

VGClassRef VGLabelGetClass() {
    if (!kLabelClassRef) {
        VGLayerClassRef layerClass = VGLayerGetClass();
        kLabelClass.base = layerClass->base;
        kLabelClass.base.size = sizeof(struct VGLabel);
        kLabelClass.base.super = layerClass;
        kLabelClass.base.init = _labelInit;
        kLabelClass.base.deallocate = _labelDeallocate;
        kLabelClass.draw = _labelDraw;
        kLabelClassRef = &kLabelClass;
    }
    return kLabelClassRef;
}

VGLabelRef VGLabelCreate(void) {
    VGLabelRef label = VGObjectCreate(VGLabelGetClass());
    return label;
}

void VGLabelSetTitle(VGLabelRef label, const char *text) {
    if (label->title) {
        free(label->title);
    }
    if (text) {
        label->title = strdup(text);
    }
}

const char *VGLabelGetTitle(VGLabelRef label) {
    return label->title;
}

void VGLabelSetTextColor(VGLabelRef label, VGColor color) {
    label->textColor = color;
}

void VGLabelSetFont(VGLabelRef label, VGFontRef font) {
    VGRelease(label->font);
    label->font = VGRetain(font);
}

VGFontRef VGLabelGetFont(VGLabelRef label) {
    return label->font;
}

