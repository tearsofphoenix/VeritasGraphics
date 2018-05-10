//
//  VGCheckBox.h
//  example_gl3
//
//  Created by Isaac on 2018/5/9.
//

#ifndef VGCheckBox_h
#define VGCheckBox_h

#include "VGLayer.h"

VG_BEGIN

typedef struct VGCheckBox *VGCheckBoxRef;

extern VGCheckBoxRef VGCheckBoxCreate(void);

extern void VGCheckBoxSetHint(VGCheckBoxRef box, const char *hint);
extern const char *VGCheckBoxGetHint(VGCheckBoxRef box);

extern bool VGCheckBoxIsChecked(VGCheckBoxRef box);

extern void VGCheckBoxSetChecked(VGCheckBoxRef box, bool checked);

VG_END

#endif /* VGCheckBox_h */
