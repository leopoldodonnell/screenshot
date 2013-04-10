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
  Screenshot(CGContextRef bitmap_context, const CFStringRef format, float compression);
  ~Screenshot();
  
  // Get the raw bitmap for the Screenshot
  void *get_bitmap();

  size_t get_width();
  size_t get_height();
  size_t get_bits_per_pixel();
  
  // Write a PNG file to filename. Return true on success.
  bool write_png(const char* filename);

  // Returns a png file in CFMutableDataRef which must be released by the caller. 
  CFMutableDataRef create_img_data(size_t &length);
  
private:
  size_t  calculate_image_memory(CFMutableDataRef img_data, size_t initial_size);
  bool    store_image(CGImageDestinationRef destination);
  
private:
  CGContextRef      _bitmap_context;
  const CFStringRef _format;
  float             _compression;
};

#endif // _SCREEN_SHOT_H_
