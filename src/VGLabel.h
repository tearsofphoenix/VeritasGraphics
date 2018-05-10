//
//  VGLabel.h
//  example_gl3
//
//  Created by Isaac on 2018/5/7.
//

#ifndef VGLabel_h
#define VGLabel_h

#include "VGLayer.h"
#include "VGFont.h"

VG_BEGIN

typedef struct VGLabel *VGLabelRef;

extern VGClassRef VGLabelGetClass(void);

extern VGLabelRef VGLabelCreate(void);

extern void VGLabelSetTitle(VGLabelRef label, const char *text);

extern const char *VGLabelGetTitle(VGLabelRef label);

extern void VGLabelSetTextColor(VGLabelRef label, VGColor color);

extern void VGLabelSetFont(VGLabelRef label, VGFontRef font);

extern VGFontRef VGLabelGetFont(VGLabelRef label);

VG_END

#endif /* VGLabel_h */
