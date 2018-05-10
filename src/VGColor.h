//
//  VGColor.h
//  example_gl3
//
//  Created by Isaac on 2018/5/9.
//

#ifndef VGColor_h
#define VGColor_h


#include "VGDefine.h"
VG_BEGIN

struct VGColor {
    float r;
    float g;
    float b;
    float alpha;
};

typedef struct VGColor VGColor;

static inline VGColor VGColorMake(float r, float g, float b, float a) {
    VGColor color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.alpha = a;
    return color;
}

static inline VGColor VGColorWhiteWithAlpha(float a) {
    return VGColorMake(1, 1, 1, a);
}

static inline VGColor VGColorBlackWithAlpha(float a) {
    return VGColorMake(0, 0, 0, a);
}

static inline VGColor VGColorWithAlpha(VGColor color, float alpha) {
    return VGColorMake(color.r, color.g, color.b, alpha);
}

extern VGColor kVGColorWhite;

extern VGColor kVGColorBlack;

extern VGColor kVGColorRed;

extern VGColor kVGColorGreen;

extern VGColor kVGColorYellow;

extern VGColor kVGColorClear;

VG_END


#endif /* VGColor_h */
