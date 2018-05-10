//
//  VGFont.c
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#include "VGFont.h"
#include "VGObjectInternal.h"
#include <stdlib.h>
#include <string.h>

static struct VGClass kFontClass;
static VGClassRef kFontClassRef = NULL;

struct VGFont {
    VGObject base;
    const char *name;
    float size;
};

static void _fontDeallocate(VGObjectRef object) {
    
    VGFontRef font = (VGFontRef)object;
    if (font->name) {
        free((void *)font->name);
    }
    CALL_SUPER(object, VGClassRef, deallocate);
}

VGClassRef VGFontGetClass() {
    if (!kFontClassRef) {
        kFontClass = kVGBaseClass;
        kFontClass.size = sizeof(struct VGFont);
        kFontClass.super = &kVGBaseClass;
        kFontClass.deallocate = _fontDeallocate;
        kFontClassRef = &kFontClass;
    }
    return kFontClassRef;
}

static VGFontRef kDefaultFont = NULL;

VGFontRef VGFontGetDefault(void) {
    if (!kDefaultFont) {
        kDefaultFont = VGFontCreate("sans", 18);
    }
    return kDefaultFont;
}

VGFontRef VGFontCreate(const char *fontName, float size) {
    VGFontRef font = (VGFontRef)VGObjectCreate(VGFontGetClass());
    font->name = strdup(fontName);
    font->size = size;
    return font;
}

void VGFontApply(VGContextRef ctx, VGFontRef font) {
    VGContextSetFont(ctx, font->name);
    VGContextSetFontSize(ctx, font->size);
}

float VGFontGetSize(VGFontRef font) {
    return font->size;
}

const char *VGFontGetName(VGFontRef font) {
    return font->name;
}
