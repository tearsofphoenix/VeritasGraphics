//
//  VGSpinner.h
//  example_gl3
//
//  Created by Isaac on 2018/5/8.
//

#ifndef VGSpinner_h
#define VGSpinner_h

#include "VGLayer.h"
#include "VGFont.h"

VG_BEGIN

typedef struct VGSpinner *VGSpinnerRef;

extern VGSpinnerRef VGSpinnerCreate(void);

extern void VGSpinnerSetT(VGSpinnerRef spinner, float t);

extern void VGSpinnerSetStartColor(VGSpinnerRef spinner, VGColor color);
extern VGColor VGSpinnerGetStartColor(VGSpinnerRef spinner);

extern void VGSpinnerSetEndColor(VGSpinnerRef spinner, VGColor color);
extern VGColor VGSpinnerGetEndColor(VGSpinnerRef spinner);

VG_END

#endif /* VGSpinner_h */
