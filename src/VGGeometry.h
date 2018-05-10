//
//  VGGeometry.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGGeometry_h
#define VGGeometry_h

#include "VGDefine.h"
#include <stdbool.h>

VG_BEGIN

struct VGPoint {
    float x;
    float y;
};

typedef struct VGPoint VGPoint;

static inline VGPoint VGPointMake(float x, float y) {
    VGPoint p;
    p.x = x;
    p.y = y;
    return p;
}

extern VGPoint VGPointZero;

static inline bool VGPointEqual(VGPoint p1, VGPoint p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

struct VGSize {
    float width;
    float height;
};

typedef struct VGSize VGSize;

static inline VGSize VGSizeMake(float w, float h) {
    VGSize size;
    size.width = w;
    size.height = h;
    return size;
}

struct VGRect {
    struct VGPoint origin;
    struct VGSize size;
};

typedef struct VGRect VGRect;

static inline VGRect VGRectMake(float x, float y, float w, float h) {
    VGRect rect;
    rect.origin = VGPointMake(x, y);
    rect.size = VGSizeMake(w, h);
    return rect;
}

static inline float VGRectMidX(VGRect rect) {
    return rect.origin.x + rect.size.width / 2.0f;
}

static inline float VGRectMaxX(VGRect rect) {
    return rect.origin.x + rect.size.width;
}

static inline float VGRectMinX(VGRect rect) {
    return rect.origin.x;
}

static inline float VGRectMaxY(VGRect rect) {
    return rect.origin.y + rect.size.height;
}

static inline float VGRectMinY(VGRect rect) {
    return rect.origin.y;
}

static inline float VGRectMidY(VGRect rect) {
    return rect.origin.y + rect.size.height / 2.0f;
}

static inline bool VGRectContainsPoint(VGRect rect, VGPoint point) {
    return VGRectMinX(rect) <= point.x && VGRectMaxX(rect) >= point.x
    && VGRectMinY(rect) <= point.y && VGRectMaxY(rect) >= point.y;
}

VG_END

#endif /* VGGeometry_h */
