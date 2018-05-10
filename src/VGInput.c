//
//  VGInput.c
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#include "VGInput.h"
#include "VGLayerInternal.h"
#include "VGContext.h"
#include "VGGradient.h"
#include "VGFont.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

struct VGInput {
    struct VGLayer base;
    const char *placeHolder;
    const char *value;
    bool showIndicator;
};

void _VGInputAppendChar(VGInputRef input, char c);

void _VGInputRemoveLastChar(VGInputRef input);

static void _inputDraw(VGLayerRef layer) {
    CALL_SUPER(layer, VGLayerClassRef, draw);
    
    VGRect frame = VGLayerGetFrame(layer);
    float x = frame.origin.x;
    float y = frame.origin.y;
    float w = frame.size.width;
    float h = frame.size.height;
    VGContextRef ctx = VGGetCurrentContext();
    
    VGContextBeginPath(ctx);
    VGContextRoundedRect(ctx, frame, 4, 1);
    VGGradientRef gradient = VGGradientCreate(VGColorMake(1, 1, 1, 32.0f / 255.0f), VGColorMake(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f));
    VGContextDrawBoxlGradient(ctx, gradient, VGRectMake(x + 1, y + 1 + 1.5f, w-2, h-2), 3, 4);
    VGContextFill(ctx);
    VGRelease(gradient);
    
    VGContextBeginPath(ctx);
    VGContextRoundedRect(ctx, frame, 4, 0.5f);
    VGContextSetStrokeColor(ctx, VGColorMake(0, 0, 0, 48.0f / 255.0f));
    VGContextStroke(ctx);
    
    VGInputRef input = (VGInputRef)layer;
    
    if (VGLayerGetFocused(layer)) {
        // draw indicator
        if (input->value) {
            // draw text
            VGFontRef font = VGFontGetDefault();
            VGFontApply(ctx, font);
            
            VGContextSetFillColor(ctx, kVGColorBlack);
            VGContextSetTextAlign(ctx,  NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
            VGContextDrawText(ctx, x, y + h * 0.5f, input->value);
            
            x += VGContextMeasureText(ctx, input->value);
        }
        
        if (input->showIndicator) {
            float min = MIN(x + 2, VGRectMaxX(frame));
            VGContextBeginPath(ctx);
            VGContextSetFillColor(ctx, kVGColorBlack);
            VGContextRect(ctx, VGRectMake(min, y + 2, 1, h - 4));
            VGContextFill(ctx);
            input->showIndicator = false;
        } else {
            input->showIndicator = true;
        }
    } else {
        if (input->placeHolder) {
            VGFontRef font = VGFontGetDefault();
            VGFontApply(ctx, font);
            VGContextSetFillColor(ctx, VGColorMake(1, 1, 1, 64.0f / 255.0f));
            VGContextSetTextAlign(ctx,  NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
            VGContextDrawText(ctx, x + h * 0.3f, y + h * 0.5f, input->placeHolder);
        }
    }
}

static bool _inputDispatch(VGLayerRef layer, VGEventRef event) {
    VGInputRef input = (VGInputRef)layer;
    VGEventType type = VGEventGetType(event);
    int button = VGEventGetButton(event);
    int action = VGEventGetAction(event);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // click event
        VGLayerSetFocused(layer, true);
        return true;
    } else if (type == kVGEventText) {
        unsigned int codepoint = VGEventGetCodePoint(event);
        _VGInputAppendChar(input, codepoint);
        printf("%d\n", codepoint);
        return true;
    } else if (type == kVGEventKey) {
        int key = VGEventGetKey(event);
        if (key == GLFW_KEY_DELETE || key == GLFW_KEY_BACKSPACE) {
            // delete a char
            _VGInputRemoveLastChar(input);
            return true;
        }
    }
    return false;
}


static struct VGLayerClass kVGInputClass;
static VGLayerClassRef kVGInputClassRef = NULL;

static VGLayerClassRef VGInputGetClass(void) {
    if (!kVGInputClassRef) {
        VGLayerClassRef layerClass = VGLayerGetClass();
        kVGInputClass.base = layerClass->base;
        kVGInputClass.base.super = (VGClassRef)layerClass;
        kVGInputClass.base.size = sizeof(struct VGInput);
        kVGInputClass.draw = _inputDraw;
        kVGInputClass.dispatch = _inputDispatch;
        kVGInputClassRef = &kVGInputClass;
    }
    return kVGInputClassRef;
}

VGInputRef VGInputCreate(void) {
    VGInputRef input = (VGInputRef)VGObjectCreate((VGClassRef)VGInputGetClass());
    return input;
}

void VGInputSetPlaceholder(VGInputRef input, const char *placeHolder) {
    if (input->placeHolder) {
        free((void *)input->placeHolder);
    }
    input->placeHolder = strdup(placeHolder);
}

const char * VGInputGetValue(VGInputRef input) {
    return input->value;
}

void VGInputSetValue(VGInputRef input, const char *value) {
    if (input->value) {
        free((void *)input->value);
    }
    input->value = strdup(value);
}

void _VGInputAppendChar(VGInputRef input, char c) {
    const char *current = input->value;
    if (current && strlen(current) > 0) {
        int length = (int)strlen(current) + 1 + 1;
        char *str = malloc(length * sizeof(char));
        strcat(str, current);
        str[length - 1] = '\0';
        str[length - 2] = c;
        input->value = str;
        free((void *)current);
    } else {
        char *str = malloc(sizeof(c) * 2);
        str[1] = '\0';
        str[0] = c;
        input->value = str;
    }
}

void _VGInputRemoveLastChar(VGInputRef input) {
    const char *current = input->value;
    if (current && strlen(current) > 0) {
        int length = (int)strlen(current);
        char *str = malloc(length * sizeof(char));
        memcpy(str, current, length * sizeof(char));
        str[length - 1] = '\0';
        input->value = str;
        free((void *)current);
    }
}

