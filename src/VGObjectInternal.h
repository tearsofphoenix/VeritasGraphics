//
//  VGObjectInternal.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGObjectInternal_h
#define VGObjectInternal_h
    
#include "VGObject.h"
    
#include <stdint.h>
#include <stddef.h>

VG_BEGIN

typedef struct VGObject *__VGObjectRef;
    typedef VGObjectRef (* VGAllocator)(size_t size);
    
    typedef void (* VGDeallocator)(VGObjectRef object);
    
    typedef void (* VGInitFunc)(void *memory);
    
    struct VGClass {
        VGClassRef super;
        size_t size;
        VGAllocator allocate;
        VGDeallocator deallocate;
        VGInitFunc init;
    };
    
    struct VGObject {
        VGClassRef isa;
        size_t ref;
    };
    
    extern VGClass kVGBaseClass;
    
#ifndef CALL_SUPER
#define CALL_SUPER(obj, SC, FUNC) ((SC)((__VGObjectRef)obj)->isa->super)->FUNC((void *)obj)
#endif
    
#ifndef CALL_SUPER2

#define CALL_SUPER2(obj, SC, FUNC) do { \
    VGClassRef __clsLooper = (VGObjectRef)obj)->isa->super; \
    while(__clsLooper) { \
        if (__clsLooper->FUNC) { __clsLooper->FUNC(obj); break; } \
        __clsLooper = __clsLooper->super; \
    } \
} while(0) \

#endif

#ifndef CALL_SUPER3

#define CALL_SUPER3(obj, CLS, FUNC, ...) do { \
    CLS __clsLooper = (CLS)(((__VGObjectRef)obj)->isa->super); \
    while(__clsLooper) { \
        if (__clsLooper->FUNC) { __clsLooper->FUNC(obj, __VA_ARGS__); break; } \
            __clsLooper = (CLS)((VGClassRef)__clsLooper)->super; \
        } \
    } while(0) \

#endif
    
#ifndef CALL_METHOD
    
#define CALL_METHOD(obj, CLS, FUNC) do { \
        CLS __clsLooper = (CLS)(((__VGObjectRef)obj)->isa); \
        while(__clsLooper) { \
            if (__clsLooper->FUNC) { __clsLooper->FUNC(obj); break; } \
            __clsLooper = (CLS)((VGClassRef)__clsLooper)->super; \
        } \
    } while(0) \

#endif

#ifndef CALL_METHOD2
    
#define CALL_METHOD2(obj, CLS, FUNC, ...) do { \
        CLS __clsLooper = (CLS)(((VGObjectRef)obj)->isa); \
        while(__clsLooper) { \
            if (__clsLooper->FUNC) { __clsLooper->FUNC(obj, __VA_ARGS__); break; } \
                __clsLooper = (CLS)((VGClassRef)__clsLooper)->super; \
            } \
        } while(0) \

#endif

#ifndef METHOD
#define METHOD(CLS, obj, FUNC) ((CLS)((__VGObjectRef)(obj))->isa)->FUNC
#endif
    
VG_END

#endif /* VGObjectInternal_h */
