//
//  VGObject.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGObject_h
#define VGObject_h

#include "VGDefine.h"

VG_BEGIN

typedef struct VGObject VGObject;

typedef const void *VGObjectRef;

typedef struct VGClass VGClass;

typedef struct VGClass *VGClassRef;

extern VGClassRef VGGetClass(VGObjectRef object);

extern VGObjectRef VGObjectCreate(VGClassRef cls);

extern VGObjectRef VGRetain(VGObjectRef object);

extern void VGRelease(VGObjectRef object);

VG_END

#endif /* VGObject_h */
