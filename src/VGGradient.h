//
//  VGGradient.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGGradient_h
#define VGGradient_h

#include "VGGeometry.h"
#include "VGTypes.h"
#include "VGColor.h"

VG_BEGIN

typedef struct VGGradient *VGGradientRef;

extern VGGradientRef VGGradientCreate(VGColor startColor, VGColor endColor);

VG_END

#endif /* VGGradient_h */
