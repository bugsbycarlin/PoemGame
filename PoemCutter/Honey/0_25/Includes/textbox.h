/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

// SDL, for window, user input, and media
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

// Standard libraries
#include <stdio.h>
#include <cstdlib>
#include <string>

// Honey includes
#include "primitives.h"
#include "graphics.h"
#include "sprite.h"

using namespace std;

namespace Honey {
  /*!
    The Textbox class holds a textbox of a particular size and font, and prints it to the screen.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/24/lets-make-honey-version-0-11-fonts-and-text

    http://www.friendsonmountains.com/blog/2018/08/31/lets-make-honey-version-0-15-sprites

    http://www.friendsonmountains.com/blog/2018/09/20/lets-make-honey-version-0-16-sequences
  */
  class Textbox : public Sprite {
   public:
    /*!
      Public constructor. Makes one Textbox.
      
      @param font_path OS valid path to a ttf font file (eg "Fonts/crayon.ttf").
      @param font_size The size of the font.
      @param text The text of the box.
      @param pos The position of the textbox on screen.
      @param color A hex string color (eg "#FCFCFC") which will be the color of the text.
      @return a Textbox, of course.
      
    */
    Textbox(string font_path, int font_size, string text, position pos, string color);

    /*!
      Get the width of the Textbox.

      @returns width of the Textbox.
    */
    int getWidth();

    /*!
      Get the height of the Textbox.

      @returns height of the Textbox.
    */
    int getHeight();

    /*!
      Set the text of the Textbox.
      
      @param text The text of the box.
    */
    void setText(string text);

    /*!
      Set the color of the text Textbox.
      
      @param color A hex string color (eg "#FCFCFC") which will be the color of the text.
    */
    void setColor(string color);

    /*!
      Public destructor. Called when you call delete on a Textbox.
    */
    ~Textbox();

   private:
    SDL_Surface* text_surface;
    TTF_Font* font;
    SDL_Color text_color;

    string text;

    int width;
    int height;

    void remakeBox();
  };
}
