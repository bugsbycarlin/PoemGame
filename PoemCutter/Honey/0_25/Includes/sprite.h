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

// Honey includes
#include "primitives.h"
#include "effects.h"
#include "graphics.h"

using namespace std;

namespace Honey {
  /*!
    The Sprite class models a sprite; a sprite is a 2d image with a position on screen and its own draw method.

    In Honey, the sprite class exists as a convenience to hold the logic for several animation methods.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/08/31/lets-make-honey-version-0-15-sprites

    http://www.friendsonmountains.com/blog/2018/09/20/lets-make-honey-version-0-16-sequences
  */
  class Sprite {
   public:

    /*!
      Public constructor. Makes one Sprite.
      
      @param draw_label The label of an image loaded in the graphics system.
      @param pos The position of the sprite on screen.
      @param color A hex string color (eg "#FCFCFC") to color the sprite.
      @param opacity value from 0 (invisible) to 1 (fully opaque).
      @param rotation desired clockwise rotation of the image on the screen in degrees.
      @param scale desired scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
      @return a Sprite, of course.
    */
    Sprite(string draw_label, position pos, string color, float opacity, float rotation, float scale);

    /*!
      Get the draw label of the Sprite.

      @return draw_label of the Sprite.
    */
    string getLabel();

    /*!
      Set the draw_label of the Sprite.

      @param draw_label The label of an image loaded in the graphics system.
    */
    void setLabel(string draw_label);

    /*!
      Get the position of the Sprite.

      @return position of the Sprite.
    */
    position getPosition();

    /*!
      Set the position of the Sprite.

      @param pos The position of the sprite on screen.
    */
    void setPosition(position pos);

    /*!
      Set the position of the Sprite with a default animation.

      @param pos The position of the sprite on screen.
      @param animation_duration how long to animate between the old position and the new one.
    */
    void setPosition(position pos, float animation_duration);

    /*!
      Shake the position of the Sprite for a while.

      @param shake_width how big the shake, how big the shake.
      @param animation_duration how long to shake the sprite.
    */
    void shakePosition(int shake_width, float animation_duration);

    /*!
      Get the color of the Sprite.

      @return color of the Sprite.
    */
    string getColor();

    /*!
      Set the color of the Sprite.

      @param color A hex string color (eg "#FCFCFC") to color the sprite.
    */
    void setColor(string color);

    /*!
      Set the color of the Sprite with a default animation.

      @param color A hex string color (eg "#FCFCFC") to color the sprite.
      @param animation_duration how long to animate between the old position and the new one.
    */
    void setColor(string color, float animation_duration);

    /*!
      Get the opacity of the Sprite.

      @return opacity of the Sprite.
    */
    float getOpacity();

    /*!
      Set the opacity of the Sprite.

      @param opacity value from 0 (invisible) to 1 (fully opaque).
    */
    void setOpacity(float opacity);

    /*!
      Set the opacity of the Sprite with a default animation.

      @param opacity value from 0 (invisible) to 1 (fully opaque).
      @param animation_duration how long to animate between the old position and the new one.
    */
    void setOpacity(float opacity, float animation_duration);

    /*!
      Fade the opacity of the Sprite from 0 to 1 to 0 with a default animation.

      @param animation_duration how long to animate from 0 to 1 to 0.
    */
    void fadeInOut(float animation_duration);

    /*!
      Get the rotation of the Sprite.

      @return rotation of the Sprite.
    */
    float getRotation();

    /*!
      Set the rotation of the Sprite.
    */
    void setRotation(float rotation);

    /*!
      Set the rotation of the Sprite with a default animation.

      @param animation_duration how long to animate between the old position and the new one.
    */
    void setRotation(float rotation, float animation_duration);

    /*!
      Get the scale of the Sprite.

      @return scale of the Sprite.
    */
    float getScale();

    /*!
      Set the scale of the Sprite.

      @param scale desired scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
    */
    void setScale(float scale);

    /*!
      Set the scale of the Sprite with a default animation.

      @param scale desired scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
      @param animation_duration how long to animate between the old position and the new one.
    */
    void setScale(float scale, float animation_duration);

    /*!
      Draw the Sprite.
    */
    void draw();

    /*!
      Draw the Sprite with an override position (useful for cloning a sprite many times in one frame).
    */
    void draw(position pos);

    /*!
      Public destructor. Called when you call delete on a Sprite.
    */
    ~Sprite();

   protected:
    string draw_label;
    string unique_label; // we can't use the same draw label for a hundred sprites with different effects.
    position pos;
    string color;
    float opacity;
    float scale;
    float rotation;
    bool centered;

    static int unique_count;
  };
}
