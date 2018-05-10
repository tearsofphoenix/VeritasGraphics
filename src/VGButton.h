//
//  VGButton.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGButton_h
#define VGButton_h

#include "VGLayer.h"
#include "VGFont.h"
#include "VGLabel.h"

VG_BEGIN

typedef struct VGButton *VGButtonRef;

typedef void (* VGButtonClickCallback)(VGButtonRef button, const void *data);

extern VGButtonRef VGButtonCreate(void);

extern VGLabelRef VGButtonGetLabel(VGButtonRef button);

extern void VGButtonSetIcon(VGButtonRef button, int icon);

extern int VGButtonGetIcon(VGButtonRef button);

extern void VGButtonSetClickCallback(VGButtonRef button, VGButtonClickCallback callback, const void *userData);

VG_END

#endif /* VGButton_h */
