//
//  VGFont.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGFont_h
#define VGFont_h

#ifdef __cplusplus
extern "C" {
#endif

#include "VGContext.h"
    
    typedef struct VGFont *VGFontRef;
    
    extern VGFontRef VGFontCreate(const char *fontName, float size);
    
    extern VGFontRef VGFontGetDefault(void);
    
    extern void VGFontApply(VGContextRef ctx, VGFontRef font);
    
    extern float VGFontGetSize(VGFontRef font);
    
    extern const char *VGFontGetName(VGFontRef font);
    
#ifdef __cplusplus
}
#endif

#endif /* VGFont_h */
