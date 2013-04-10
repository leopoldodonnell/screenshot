//
//
//  screen_shot.cpp
//
//  Created by Leopold O'Donnell on 3/18/13.
//  MIT-LIcense Copyright (c) 2013 Leo O'Donnell.
//

#include <ApplicationServices/ApplicationServices.h>
#include "screen_shot.h"


Screenshot::Screenshot(CGContextRef bitmap_context, const CFStringRef format, float compression) : 
  _bitmap_context(bitmap_context), _format(format), _compression(compression) {}

Screenshot::~Screenshot() {
  CGContextRelease(_bitmap_context); 
}

void* Screenshot::get_bitmap() {
  return CGBitmapContextGetData(_bitmap_context);
}

size_t Screenshot::get_width() {
  return CGBitmapContextGetWidth(_bitmap_context);
}

size_t Screenshot::get_height() {
  return CGBitmapContextGetHeight(_bitmap_context);
}

size_t Screenshot::get_bits_per_pixel() {
  return CGBitmapContextGetBitsPerPixel(_bitmap_context);
}

bool Screenshot::write_png(const char* filepath) {
  CFURLRef url = CFURLCreateWithFileSystemPath(
    NULL, 
    CFStringCreateWithCString(NULL, filepath, kCFStringEncodingUTF8),
    kCFURLPOSIXPathStyle,
    false);
  CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, _format, 1, NULL);
  
  store_image(destination);
    
  CFRelease(destination);

  return true;
}

CFMutableDataRef Screenshot::create_img_data(size_t &length) {
  
  length = get_width() * get_height() * (get_bits_per_pixel()/8);
  
  CFMutableDataRef img_data         = CFDataCreateMutable(NULL, length);
  CGImageDestinationRef destination = CGImageDestinationCreateWithData(img_data, _format, 1, NULL);
  
  if (!store_image(destination)) {
    length = 0;
  }
  
  length = calculate_image_memory(img_data, length);
    
  CFRelease(destination);
  
  return img_data;  
}

/*
 * Calculate the actual size used by an image.
 */
size_t Screenshot::calculate_image_memory(CFMutableDataRef img_data, size_t initial_size) {
  UInt8 *data = CFDataGetMutableBytePtr(img_data);

  size_t real_size = initial_size / 4;  // Its already seriously compressed, so reduce the start value
  
  // Traverse backwards until there's some data
  while (data[real_size] == 0) {
    --real_size;
  }
  // You'll have gone too far, add 1
  return real_size + 1;  
}

bool Screenshot::store_image(CGImageDestinationRef destination) {
  CGImageRef image = CGBitmapContextCreateImage(_bitmap_context);

  CFStringRef myKeys[1];
  CFTypeRef myValues[1];
  CFDictionaryRef myOptions = NULL;
  myKeys[0] = kCGImageDestinationLossyCompressionQuality;
  myValues[0] = CFNumberCreate(NULL, kCFNumberFloatType, &_compression);
  myOptions = CFDictionaryCreate(NULL, (const void**)myKeys, (const void**)myValues, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
  
  CGImageDestinationAddImage(destination, image, myOptions);

  if (!CGImageDestinationFinalize(destination)) {
      fprintf(stderr, "Failed to write image to destination\n");
      return false;
  }
  
  CFRelease(image);
  CFRelease(myOptions);
  
  return true;
}