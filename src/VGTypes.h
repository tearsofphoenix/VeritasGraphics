//
//  VGTypes.h
//  tutorial02_red_triangle
//
//  Created by Isaac on 2018/5/3.
//

#ifndef VGTypes_h
#define VGTypes_h

#include "VGDefine.h"
VG_BEGIN

typedef enum {
    kVGInterpolationNone,
    kVGInterpolationLow,
    kVGInterpolationMiddle,
    kVGInterpolationHigh
} VGInterpolationQuality;

typedef enum {
    kVGLineCapButt,
    kVGLineCapRound,
    kVGLineCapSquare,
} VGLineCap;

typedef enum {
    kVGLineJoinMiter,
    kVGLineJoinRound,
    kVGLineJoinBevel
} VGLineJoin;

typedef enum {
    kVGPathFill,
    kVGPathEOFill,
    kVGPathStroke,
    kVGPathFillStroke,
    kVGPathEOFillStroke,
} VGPathDrawingMode;

VG_END

#endif /* VGTypes_h */
