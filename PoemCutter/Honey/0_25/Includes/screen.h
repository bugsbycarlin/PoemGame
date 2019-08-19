/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

// Standard libraries
#include <stdio.h>
#include <cstdlib>
#include <string>

using namespace std;

namespace Honey {
  /*!
    The Screen class models one game screen. A game screen can be initialized and can run a loop iteration.

    This is a virtual class meant to be overridden by a set of specific game screens.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/09/21/lets-make-honey-version-0-17-screens
  */
  class Screen {
   public:

    /*!
      Public constructor. Makes one Screen.
      
      @return a Screen, of course.
    */
    Screen();

    /*!
      Initialize this game screen.
    */
    virtual void initialize();

    /*!
      Run an iteration of the game loop.
    */
    virtual void loop();

    /*!
      Public destructor. Called when you call delete on a Screen.
    */
    virtual ~Screen();
  };
}
