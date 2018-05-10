//
//  VGObject.c
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#include "VGObjectInternal.h"
#include <stdlib.h>

static VGObjectRef _allocator(size_t size) {
    return calloc(1, size);
}

static void _deallocate(VGObjectRef object) {
    free((void *)object);
}

static void _init(void *memory) {
    ;
}

VGClass kVGBaseClass = {
    .super = NULL,
    .size = sizeof(VGObject),
    .allocate = _allocator,
    .deallocate = _deallocate,
    .init = _init
};

VGObjectRef VGObjectCreate(VGClassRef cls) {
    __VGObjectRef object = (__VGObjectRef)cls->allocate(cls->size);
    object->isa = cls;
    object->ref = 1;
    CALL_METHOD(object, VGClassRef, init);
    return object;
}

VGClassRef VGGetClass(VGObjectRef object) {
    return ((__VGObjectRef)object)->isa;
}

VGObjectRef VGRetain(VGObjectRef obj) {
    __VGObjectRef object = (__VGObjectRef)obj;
    if (object) {
        ++object->ref;
    }
    return object;
}

void VGRelease(VGObjectRef obj) {
    __VGObjectRef object = (__VGObjectRef)obj;
    if (object) {
        --object->ref;
        if (object->ref == 0) {
            object->isa->deallocate(object);
        }
    }
}
