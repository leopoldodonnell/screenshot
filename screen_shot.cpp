//
//
//  screen_shot.cpp
//
//  Created by Leopold O'Donnell on 3/18/13.
//  MIT-LIcense Copyright (c) 2013 Leo O'Donnell.
//

#include <ApplicationServices/ApplicationServices.h>
#include "screen_shot.h"


Screenshot::Screenshot(CGContextRef bitmap_context) : _bitmap_context(bitmap_context) {}

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
  CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
  
  store_image(destination);
    
  CFRelease(destination);

  return true;
}

CFMutableDataRef Screenshot::create_png_data(size_t &length) {
  
  length = get_width() * get_height() * (get_bits_per_pixel()/8);
  
  CFMutableDataRef png_data         = CFDataCreateMutable(NULL, length);
  CGImageDestinationRef destination = CGImageDestinationCreateWithData(png_data, kUTTypePNG, 1, NULL);
  
  if (!store_image(destination)) {
    length = 0;
  }
  
  CFRelease(destination);
  
  return png_data;  
}

bool Screenshot::store_image(CGImageDestinationRef destination) {
  CGImageRef image = CGBitmapContextCreateImage(_bitmap_context);

  CGImageDestinationAddImage(destination, image, nil);

  if (!CGImageDestinationFinalize(destination)) {
      fprintf(stderr, "Failed to write image to destination\n");
      return false;
  }
  
  CFRelease(image);
  
  return true;
}