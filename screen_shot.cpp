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

bool Screenshot::write_png(const char* filepath) {
  CFURLRef url = CFURLCreateWithFileSystemPath(
    NULL, 
    CFStringCreateWithCString(NULL, filepath, kCFStringEncodingUTF8),
    kCFURLPOSIXPathStyle,
    false);
  CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
  
  CGImageRef image = CGBitmapContextCreateImage(_bitmap_context);

  CGImageDestinationAddImage(destination, image, nil);

  if (!CGImageDestinationFinalize(destination)) {
      fprintf(stderr, "Failed to write image to %s", filepath);
      return false;
  }
  
  CFRelease(image);
  CFRelease(destination);
  return true;
}

