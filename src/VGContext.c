//
//  VGContext.c
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#include "VGContextInternal.h"
#include "VGGradientInternal.h"
#include "VGFont.h"
#include <stddef.h>
#include <stdlib.h>

static char* codepointToUTF8(int cp, char* str)
{
    int n = 0;
    if (cp < 0x80) n = 1;
    else if (cp < 0x800) n = 2;
    else if (cp < 0x10000) n = 3;
    else if (cp < 0x200000) n = 4;
    else if (cp < 0x4000000) n = 5;
    else if (cp <= 0x7fffffff) n = 6;
    str[n] = '\0';
    switch (n) {
        case 6: str[5] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x4000000;
        case 5: str[4] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x200000;
        case 4: str[3] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x10000;
        case 3: str[2] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x800;
        case 2: str[1] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0xc0;
        case 1: str[0] = cp;
    }
    return str;
}

struct VGContext {
    NVGcontext *impl;
};

static VGContextRef kCurrentContext = NULL;

static inline NVGcolor VGColorToNGColor(VGColor color) {
    return nvgRGBA(255 * color.r, 255 * color.g, 255 * color.b, 255 * color.alpha);
}

VGContextRef VGGetCurrentContext(void) {
    return kCurrentContext;
}

VGContextRef VGContextCreate(NVGcontext *impl) {
    VGContextRef ctx = malloc(sizeof(*ctx));
    ctx->impl = impl;
    kCurrentContext = ctx;
    return ctx;
}

void VGContextSetFillColor(VGContextRef ctx, VGColor color) {
    nvgFillColor(ctx->impl, VGColorToNGColor(color));
}

void VGContextFill(VGContextRef ctx) {
    nvgFill(ctx->impl);
}

void VGContextSetStrokeColor(VGContextRef ctx, VGColor color) {
    nvgStrokeColor(ctx->impl, VGColorToNGColor(color));
}

void VGContextStroke(VGContextRef ctx) {
    nvgStroke(ctx->impl);
}

void VGContextBeginPath(VGContextRef ctx) {
    nvgBeginPath(ctx->impl);
}

void VGContextCloseSubPath(VGContextRef ctx) {
    nvgClosePath(ctx->impl);
}

void VGContextRect(VGContextRef ctx, VGRect rect) {
    nvgRect(ctx->impl, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void VGContextSetFont(VGContextRef ctx, const char *fontName) {
    nvgFontFace(ctx->impl, fontName);
}

void VGContextSetFontSize(VGContextRef ctx, float size) {
    nvgFontSize(ctx->impl, size);
}

void VGContextDrawText(VGContextRef ctx, float x, float y, const char *text) {
    nvgText(ctx->impl, x, y, text, NULL);
}

void VGContextSetTextAlign(VGContextRef ctx, enum NVGalign align) {
    nvgTextAlign(ctx->impl, align);
}

void VGContextRoundedRect(VGContextRef ctx, VGRect rect, float radius, float offset) {
    float x = rect.origin.x;
    float y = rect.origin.y;
    float w = rect.size.width;
    float h = rect.size.height;
    nvgRoundedRect(ctx->impl, x + offset, y + offset, w - 2 * offset, h - 2 * offset, radius - offset);
}

void VGContextCircle(VGContextRef ctx, float cx, float cy, float radius) {
    nvgCircle(ctx->impl, cx, cy, radius);
}

void VGContextSaveState(VGContextRef ctx) {
    nvgSave(ctx->impl);
}

void VGContextRestoreState(VGContextRef ctx) {
    nvgRestore(ctx->impl);
}

void VGContextArc(VGContextRef ctx, float cx, float cy, float radius, float startAngle, float endAngle, int clockWise) {
    nvgArc(ctx->impl, cx, cy, radius, startAngle, endAngle, clockWise);
}

void VGContextDrawLinearGradient(VGContextRef ctx, VGGradientRef gradient, VGPoint startPoint, VGPoint endPoint) {
    NVGpaint p = nvgLinearGradient(ctx->impl, startPoint.x, startPoint.y, endPoint.x, endPoint.y, VGColorToNGColor(gradient->startColor), VGColorToNGColor(gradient->endColor));
    nvgFillPaint(ctx->impl, p);
}

void VGContextDrawBoxlGradient(VGContextRef ctx, VGGradientRef gradient, VGRect rect, float radius, float f) {
    float x = rect.origin.x;
    float y = rect.origin.y;
    float w = rect.size.width;
    float h = rect.size.height;
    NVGpaint bg = nvgBoxGradient(ctx->impl, x, y, w, h, radius, f, VGColorToNGColor(gradient->startColor), VGColorToNGColor(gradient->endColor));
    nvgFillPaint(ctx->impl, bg);
}

void VGContextDrawIcon(VGContextRef ctx, int icon, VGPoint position, int align) {
    char text[8];
    nvgTextAlign(ctx->impl, align);
    nvgText(ctx->impl, position.x, position.y, codepointToUTF8(icon, text), NULL);
}

void VGContextDrawIconAt(VGContextRef ctx, int icon, VGPoint position, float size, VGColor color) {
    VGFontRef font = VGFontCreate("icons", size);
    VGFontApply(ctx, font);
    VGContextSetFillColor(ctx, color);
    VGContextDrawIcon(ctx, icon, position, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    VGRelease(font);
}

float VGContextMeasureText(VGContextRef ctx, const char *text) {
    return nvgTextBounds(ctx->impl, 0, 0, text, NULL, NULL);
}
