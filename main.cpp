//
//  main.cpp
//  screenshot - Take a screenshot for all of the active displays.
//
//  Created by Leopold O'Donnell on 3/18/13.
//  MIT-LIcense Copyright (c) 2013 Leo O'Donnell.
//

#include <stdio.h>
#include <stddef.h>
#include "screen_shooter.h"

int main(int argc, const char * argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Error - Usage: screenshooter [-c compression] <filename.[jpg, jp2, png, tiff, gif, bmp]>\n");
    return 1;
  }
  
  const char* filename = "";
  float compression = 1.0;
  CFStringRef format;
  
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0) {
      compression = ::atof(argv[++i]);
    }
    else {
      filename = argv[i];
    }
  }
  
  if (strcasestr(filename, ".jpg")) {
    format = kUTTypeJPEG;
  }
  else if (strcasestr(filename, ".jp2")) {
    format = kUTTypeJPEG2000;
  }  
  else if (strcasestr(filename, ".png")) {
    format = kUTTypePNG;    
  }
  else if (strcasestr(filename, ".tiff")) {
    format = kUTTypeTIFF;    
  }
  else if (strcasestr(filename, ".gif")) {
    format = kUTTypeGIF;    
  }
  else if (strcasestr(filename, ".bmp")) {
    format = kUTTypeBMP;        
  }
  else {
    fprintf(stderr, "Error filetype for %s is not supported: Try one of [jpg, jp2, png, tiff, gif, bmp]\n", filename);
    return 1;
  }
  
  ScreenShooter shooter;
  Screenshot* screenshot = shooter.take_screenshot(format, compression);
  screenshot->write_png(filename);
  
  delete screenshot;
  
  return 0;
}
