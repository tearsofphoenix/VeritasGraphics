//
//  VGInput.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGInput_h
#define VGInput_h

#include "VGDefine.h"

VG_BEGIN

#include "VGLayer.h"

typedef struct VGInput *VGInputRef;

extern VGInputRef VGInputCreate(void);

extern void VGInputSetPlaceholder(VGInputRef input, const char *placeHolder);

extern const char * VGInputGetValue(VGInputRef input);

extern void VGInputSetValue(VGInputRef input, const char *value);

VG_END

#endif /* VGInput_h */
