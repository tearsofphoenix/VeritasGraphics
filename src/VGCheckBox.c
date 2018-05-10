//
//  VGCheckBox.c
//  example_gl3
//
//  Created by Isaac on 2018/5/9.
//

#include "VGCheckBox.h"
#include "VGLayerInternal.h"
#include "VGLabel.h"
#include "VGContextInternal.h"
#include "nanovg.h"
#include <GLFW/glfw3.h>

#define ICON_SEARCH 0x1F50D
#define ICON_CIRCLED_CROSS 0x2716
#define ICON_CHEVRON_RIGHT 0xE75E
#define ICON_CHECK 0x2713
#define ICON_LOGIN 0xE740
#define ICON_TRASH 0xE729

struct VGCheckBox {
    struct VGLayer base;
    VGGradientRef gradient;
    VGLabelRef label;
    bool checked;
};

static void _checkBoxInit(void *memory) {
    VGCheckBoxRef box = memory;
    CALL_SUPER(box, VGClassRef, init);

    box->gradient = VGGradientCreate(VGColorMake(0, 0, 0, 32 / 255.0f), VGColorMake(0, 0, 0, 92 / 255.0f));
    box->label = VGLabelCreate();
    box->checked = true;
    VGLayerAddSubLayer((VGLayerRef)box, (VGLayerRef)box->label);
}

static void _checkBoxDeallocate(VGObjectRef obj) {
    VGCheckBoxRef box = (VGCheckBoxRef)obj;
    VGRelease(box->label);
    VGRelease(box->gradient);
    
    CALL_SUPER(box, VGClassRef, deallocate);
}

static void _checkBoxDraw(VGLayerRef layer) {
    CALL_SUPER(layer, VGLayerClassRef, draw);
    VGCheckBoxRef box = (VGCheckBoxRef)layer;
    VGContextRef ctx = VGGetCurrentContext();
    VGRect frame = VGLayerGetFrame(layer);
    float x = frame.origin.x;
    float y = frame.origin.y;
    float h = frame.size.height;
    
    VGContextBeginPath(ctx);

    VGContextRoundedRect(ctx, VGRectMake(x+1,y+(int)(h*0.5f)-9, 18,18), 3, 0);
    VGContextDrawBoxlGradient(ctx, box->gradient, VGRectMake(x+1,y+(int)(h*0.5f)-9+1, 18,18), 3, 3);
    
    VGContextFill(ctx);
    
    if (box->checked) {
        VGContextDrawIconAt(ctx, ICON_CHECK, VGPointMake(x+9+2, y+h*0.5f), 40, VGColorWhiteWithAlpha(0.5));
    }
}

static bool _checkBoxDispatch(VGLayerRef layer, VGEventRef event) {
    int button = VGEventGetButton(event);
    int action = VGEventGetAction(event);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // click event
        VGCheckBoxRef box = (VGCheckBoxRef)layer;
        VGCheckBoxSetChecked(box, !VGCheckBoxIsChecked(box));
        return true;
    }
    return false;
}

static void _checkBoxSetFrame(VGLayerRef layer, VGRect frame) {
    CALL_SUPER3(layer, VGLayerClassRef, setFrame, frame);
    
    VGCheckBoxRef box = (VGCheckBoxRef)layer;
    float h = frame.size.height;
    float w = frame.size.width;
    VGLayerSetFrame((VGLayerRef)box->label, VGRectMake(28, h * 0.5f, w - 28, h));
}

static struct VGLayerClass kCheckBoxClass;

static struct VGLayerClass *kCheckBoxClassRef = NULL;

VGClassRef VGCheckBoxGetClass() {
    if (!kCheckBoxClassRef) {
        VGLayerClassRef layerClass = VGLayerGetClass();
        kCheckBoxClass.base = layerClass->base;
        kCheckBoxClass.base.size = sizeof(struct VGCheckBox);
        kCheckBoxClass.base.super = (VGClassRef)layerClass;
        kCheckBoxClass.base.init = _checkBoxInit;
        kCheckBoxClass.base.deallocate = _checkBoxDeallocate;
        kCheckBoxClass.draw = _checkBoxDraw;
        kCheckBoxClass.setFrame = _checkBoxSetFrame;
        kCheckBoxClass.dispatch = _checkBoxDispatch;
        kCheckBoxClassRef = &kCheckBoxClass;
    }
    return (VGClassRef)kCheckBoxClassRef;
}

VGCheckBoxRef VGCheckBoxCreate(void) {
    VGCheckBoxRef box = (VGCheckBoxRef)VGObjectCreate(VGCheckBoxGetClass());
    return box;
}

void VGCheckBoxSetHint(VGCheckBoxRef box, const char *hint) {
    VGLabelSetTitle(box->label, hint);
}

const char *VGCheckBoxGetHint(VGCheckBoxRef box) {
    return VGLabelGetTitle(box->label);
}

bool VGCheckBoxIsChecked(VGCheckBoxRef box) {
    return box->checked;
}

void VGCheckBoxSetChecked(VGCheckBoxRef box, bool checked) {
    box->checked = checked;
}
