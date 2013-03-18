//
//  screen_shooter.cpp
//
//  Created by Leopold O'Donnell on 3/18/13.
//  MIT-LIcense Copyright (c) 2013 Leo O'Donnell.
//
#include "screen_shooter.h"

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })


ScreenShooter::ScreenShooter() {
  init_displays();
  calculate_bounds();
}

ScreenShooter::~ScreenShooter() {
  free(_displays);
  delete [] _display_bounds;
}

Screenshot* ScreenShooter::take_screenshot() {
  CGImageRef* images = new CGImageRef[_dsp_count];
   
  /* Grab the images */
  for (unsigned int i = 0; i < _dsp_count; i++) {
     images[i] = CGDisplayCreateImage(_displays[i]);
  }

  /* Calculate size of image to produce */
  CGSize finalSize = CGSizeMake(_top_right.x - _bottom_left.x, _bottom_left.y - _top_right.y);

  /* Round out the bitmap size information */
  size_t bytesPerRow = finalSize.width * CGImageGetBitsPerPixel(images[0]) / 8;

  /* Create context around bitmap */
  CGContextRef context = CGBitmapContextCreate(
    NULL, finalSize.width, finalSize.height,
    CGImageGetBitsPerComponent(images[0]), bytesPerRow,
    CGImageGetColorSpace(images[0]), CGImageGetBitmapInfo(images[0])
  );

  /* Draw images into the bitmap */
  for (unsigned int i = 0; i < _dsp_count; i++)
  {
      /* Adjust the positions to account for coordinate system shifts
         (displays origin is at top left; image origin is at bottom left) */
      CGRect adjustedPoint = CGRectMake(_display_bounds[i].origin.x - _bottom_left.x,
                                        _bottom_left.y - _display_bounds[i].size.height - _display_bounds[i].origin.y,
                                        _display_bounds[i].size.width,
                                        _display_bounds[i].size.height);
      CGContextDrawImage(context, adjustedPoint, images[i]);
  }
  
  delete [] images;

  return new Screenshot(context);
}

/* Calculate the _bottom_left and _top_right corners of our virtual display.
 * Must be called after init_displays.
 */
void ScreenShooter::calculate_bounds() {
  _display_bounds = new CGRect[_dsp_count];
  
  for(unsigned int i = 0; i < _dsp_count; i++)
  {
      _display_bounds[i] = CGDisplayBounds(_displays[i]);
      CGRect bounds   = _display_bounds[i];
      _bottom_left.x = min(_bottom_left.x, bounds.origin.x);
      _bottom_left.y = max(_bottom_left.y, bounds.origin.y+bounds.size.height);
      _top_right.x   = max(_top_right.x, bounds.origin.x+bounds.size.width);
      _top_right.y   = min(_top_right.y, bounds.origin.y);
  }
}

/* Initialize the array and size of the Active Displays */
void ScreenShooter::init_displays() {
    /* How many active displays do we have? */
    CGGetActiveDisplayList(0, NULL, (uint32_t*)&_dsp_count);
    
    /* Allocate enough memory to hold all the display IDs we have. */
    _displays = (CGDirectDisplayID*) calloc((size_t) _dsp_count, sizeof(CGDirectDisplayID));
    
    /* Get the list of active displays */
    CGGetActiveDisplayList(_dsp_count, _displays, &_dsp_count);
}
