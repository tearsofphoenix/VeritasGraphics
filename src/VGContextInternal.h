//
//  VGContextInternal.h
//  example_gl3
//
//  Created by Isaac on 2018/5/9.
//

#ifndef VGContextInternal_h
#define VGContextInternal_h

#include "VGContext.h"

VG_BEGIN

extern void VGContextDrawIcon(VGContextRef ctx, int icon, VGPoint position, int align);

extern void VGContextDrawIconAt(VGContextRef ctx, int icon, VGPoint position, float size, VGColor color);

VG_END

#endif /* VGContextInternal_h */
