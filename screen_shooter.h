//
//  screen_shooter.h
//
//  Created by Leopold O'Donnell on 3/18/13.
//  MIT-LIcense Copyright (c) 2013 Leo O'Donnell.
//
//
#ifndef _SCREEN_SHOOTER_H_
#define _SCREEN_SHOOTER_H_

#include <ApplicationServices/ApplicationServices.h>
#include "screen_shot.h"

/**
 * A ScreenShooter provides a facility to take one of more screenshots where a screenshot
 * includes a large image of ALL active displays on a computer.
 * 
 */
class ScreenShooter {
  public:
    ScreenShooter();
    ~ScreenShooter();

    // Allocate and take a new screenshot of all active screens. The caller
    // is responsible for its deletion.
    Screenshot* take_screenshot();
  
  private:
    void calculate_bounds();
    void init_displays();
    
  private:
    CGDirectDisplayID * _displays;
    CGDisplayCount      _dsp_count;
    CGRect*             _display_bounds;
    CGPoint             _bottom_left;
    CGPoint             _top_right;
};

#endif // _SCREEN_SHOOTER_H_