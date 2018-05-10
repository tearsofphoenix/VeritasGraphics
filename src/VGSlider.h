//
//  VGSlider.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGSlider_h
#define VGSlider_h

#include "VGDefine.h"

VG_BEGIN

typedef struct VGSlider *VGSliderRef;

extern VGSliderRef VGSliderCreate(void);

extern void VGSliderSetValue(VGSliderRef slider, float value);
extern float VGSliderGetValue(VGSliderRef slider);

VG_END

#endif /* VGSlider_h */
