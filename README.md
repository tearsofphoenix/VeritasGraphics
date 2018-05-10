Veritas Graphics
==========

Veritas Graphics is a artificial graphics rendering library based on [NanoVG](https://github.com/memononen/nanovg). All APIs are learned from Apple 
[CoreGraphics](https://developer.apple.com/documentation/coregraphics) & [CoreAnimation](https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CoreAnimation_guide/Introduction/Introduction.html).

## Screenshot

![screenshot under development](/example/screenshot-01-vg.png?raw=true)

Usage
=====

The Veritas Graphics API is modeled loosely on QuartzCore API. 

## Creating Render context

```C
#include "VGContext.h"
...
struct NVGcontext* vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
VGContextCreate(vg);

```
This will create a render context, you can access this context by `extern VGContextRef VGGetCurrentContext(void)`.

## Using UI in VeritasGraphics

1. VGLabel    
2. VGButton  
3. VGSpinner  
4. VGSlider  
5. VGInput  
6. VGCheckBox 

## License
The library is licensed under [zlib license](LICENSE.txt)
