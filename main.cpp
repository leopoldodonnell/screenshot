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
  if (argc != 2) {
    fprintf(stderr, "Error - Usage: screenshooter <filename>\n");
    return 1;
  }
  
  ScreenShooter shooter;
  Screenshot* screenshot = shooter.take_screenshot();
  screenshot->write_png(argv[1]);
  delete screenshot;
  
  return 0;
}
