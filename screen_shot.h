//
//  screen_shot.h
//
//  Created by Leo O'Donnell on 3/18/13.
//
//
#ifndef _SCREEN_SHOT_H_
#define _SCREEN_SHOT_H_

/**
 * A Screenshot encapsulates a CGScontext that represents an image of a screenshot.
 * 
 * The Screenshot is expected to own the context that it is initialized with. It will
 * not increase the reference count.
 * 
 * Destruction of the Screenshot will release the context.
 */
class Screenshot {
public:
  Screenshot(CGContextRef bitmap_context);
  ~Screenshot();
  
  // Get the raw bitmap for the Screenshot
  void *get_bitmap();
  
  size_t get_width();
  size_t get_height();
  size_t get_bits_per_pixel();
  
  // Write a PNG file to filename. Return true on success.
  bool write_png(const char* filename);
  
private:
  CGContextRef _bitmap_context;
};

#endif // _SCREEN_SHOT_H_
