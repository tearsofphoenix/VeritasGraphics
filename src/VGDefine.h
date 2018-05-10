//
//  VGDef.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGDef_h
#define VGDef_h

#ifndef VG_BEGIN

#ifdef __cplusplus
#define VG_BEGIN extern "C" {
#else
#define VG_BEGIN
#endif

#endif
    
#ifndef VG_END

#ifdef __cplusplus
#define VG_END }
#else
#define VG_END
#endif

#endif

#ifndef MIN
#define MIN(a, b) ({ __typeof__ (a) _a = (a);  __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#endif

#ifndef CLAMP
#define CLAMP(a, min, max) (a < min ? min : (a > max ? max : a))
#endif

#endif /* VGDef_h */
