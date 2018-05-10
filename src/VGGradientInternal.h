//
//  VGGradientInternal.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGGradientInternal_h
#define VGGradientInternal_h

#include "VGGradient.h"
#include "VGObjectInternal.h"

VG_BEGIN

struct VGGradient {
    struct VGObject base;
    VGColor startColor;
    VGColor endColor;
};

VG_END

#endif /* VGGradientInternal_h */
