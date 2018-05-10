//
//  VGGradient.c
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#include "VGGradientInternal.h"

static VGClass kVGGradientClass;

static VGClassRef kVGGradientClassRef = NULL;

static VGClassRef VGGradientGetClass() {
    if (!kVGGradientClassRef) {
        kVGGradientClass = kVGBaseClass;
        kVGGradientClass.super = &kVGBaseClass;
        kVGGradientClass.size = sizeof(struct VGGradient);
        kVGGradientClassRef = &kVGGradientClass;
    }
    return kVGGradientClassRef;
}


VGGradientRef VGGradientCreate(VGColor startColor, VGColor endColor) {
    VGGradientRef gradient = VGObjectCreate(VGGradientGetClass());
    gradient->startColor = startColor;
    gradient->endColor = endColor;
    return gradient;
}
