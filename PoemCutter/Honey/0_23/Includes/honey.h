/*
  Honey
  Matthew Carlin
  Copyright 2018
*/

/*!
  \mainpage Honey Honey Honey Honeeeeey
 
  \section intro_sec Introduction
 
  Honey is the smooth game engine.

  It's meant for making cute mid sized indie games in C++.

  Smooth means games that are easy to write, hopefully much easier than most C++ code.

  Smooth also means games with great play control, nice effects.

  \section use_sec Setup
  
  To use, include "honey.h".

  This header file creates global singletons for window, time, math, hot_config,
  input, layouts, graphics, effects, and sound, in that order.

  To initialize, call StartHoney();

  StartHoney style 1:

  @param title the title of the game.
  @param screen_width width of the screen in pixels.
  @param screen_height height of the screen in pixels.
  @param full_screen whether to run the game in full screen mode.

  StartHoney style 2:

  @param title the title of the game.
  
  In the second case, screen_width, screen_height, and full_screen are looked up from config.txt,
  in the layout section, eg:

  int screen_width = hot_config.getInt("layout", "screen_width");
  int screen_height = hot_config.getInt("layout", "screen_height");
  bool full_screen = hot_config.getBool("layout", "full_screen");

  \section teardown_sec Tear Down

  To properly clean up Honey, do... nothing! When the global part of the stack is cleaned up,
  all the global singletons will be destroyed, taking care of themselves in the process.

  If you use Textbox pointers, be sure to delete them afterwards.

  eg, if you do:

  Textbox* score = new Textbox(...);

  be sure to finish by doing:

  delete score;
*/

#pragma once

#include "window.h"
#include "screenmanager.h"
#include "timing.h"
#include "mathutilities.h"
#include "hotconfig.h"
#include "input.h"
#include "collisions.h"
#include "effects.h"
#include "graphics.h"
#include "layouts.h"
#include "sprite.h"
#include "textbox.h"
#include "menu.h"
#include "sound.h"

using namespace std;

namespace Honey {

  void StartHoney(string title, int screen_width, int screen_height, bool full_screen);
  void StartHoney(string title);
}
