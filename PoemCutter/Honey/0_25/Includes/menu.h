/*!
  @Honey
  @author Matthew Carlin
  Copyright 2019
*/

#pragma once

// SDL, for window, user input, and media
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

// Standard libraries
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

// Honey includes
#include "textbox.h"
#include "hotconfig.h"

using namespace std;

namespace Honey {
  /*!
    The Menu class holds a menu, ie, a background with printed text on it.

    Primarily covered in blog posts:

    None yet!
  */
  class Menu {
   public:
    /*!
      Public constructor. Makes one Menu.

      Starting with image_file_root, Menu looks for nine component pictures.
      Let's say the location is "Art/" and the root is "gradient_menu".
      The constructor will load:
      Art/gradient_menu_border_top_left.png
      Art/gradient_menu_border_left.png
      Art/gradient_menu_border_bottom_left.png
      Art/gradient_menu_border_top.png
      Art/gradient_menu_center.png
      Art/gradient_menu_border_bottom.png
      Art/gradient_menu_border_top_right.png
      Art/gradient_menu_border_right.png
      Art/gradient_menu_border_bottom_right.png

      It will then use these, and the width and height parameters, to fill
      an SDL surface, assuming these graphics fit together seamlessly, and that top,
      left, bottom, right, and center may be tiled as necessary.

      @param x x coordinate of the menu on screen.
      @param y y coordinate of the menu on screen.
      @param width width of the menu.
      @param height height of the menu.
      @param image_location The location of menu image components.
      @param image_root The root name of a set of images. See comments above.
      @param margin_x x coordinate of text relative to menu top left.
      @param margin_y y coordinate of text relative to menu top left.
      @param num_lines number of lines of text allowed.
      @param wrap_length number of characters allowed before wrapping.
      @param typewriter boolean determinine whether menu text is animated one character at a time
      @param typewriter_delay typewriter delay in seconds per character. Keep it small!
      @param font_path OS valid path to a ttf font file (eg "Fonts/crayon.ttf").
      @param font_size The size of the font.
      @param font_color A hex string color (eg "#FCFCFC") which will be the color of the text.
      @return a Menu.
      
    */
    Menu(
      int x,
      int y,
      int width,
      int height,
      string image_location,
      string image_root,
      int margin_x,
      int margin_y,
      int num_lines,
      int wrap_length,
      bool typewriter,
      float typewriter_delay,
      string font_path,
      int font_size,
      string font_color
    );

    /*!
      Public constructor. Makes one Menu.

      Initializes a menu using values drawn from config.

      @param image_root the location of art files
      @param section config section for lookup.
      @param name_root config root name for lookup.
      @return a Menu.
      
    */
    Menu(string image_location, string section, string name_root);

    /*!
      Set the text of the Menu, using wrap_length to auto-wrap into lines.
      
      @param text The text of the menu.
    */
    void setText(string text);

    /*!
      Set the text of the Menu, using a pre-calculated vector of lines.
      
      @param text The text of the box.
    */
    void setTextLines(vector<string> lines);

    /*!
      Set the color of a line of the Menu.
      
      @param int line The line number to set.
      @param color string hex color, eg #FFFFFF.
    */
    void setLineColor(int line, string color);

    /*!
      Draw the Menu
    */
    void draw();

    /*!
      Start the typewriter effect (or reset it).
    */
    void startTypewriter();

    /*!
      Finish the typewriter effect (ie, display all the text).
    */
    void finishTypewriter();

    /*!
      Return true iff the typewriter effect is finished (ie all text is displayed).
    */
    bool typewriterFinished();

    /*!
      Public destructor. Called when you call delete on a Menu.
    */
    ~Menu();

   protected:
    static int unique_count;

   private:
    void setupMenu(
      string image_location,
      string image_root,
      string font_path,
      int font_size,
      string font_color
    );
    void makeTextboxes();

    vector<Textbox*> textboxes;
    vector<string> text_lines;

    bool background;

    int x;
    int y;
    int width;
    int height;
    string image;
    int margin_x;
    int margin_y;
    int num_lines;
    int wrap_length;
    bool typewriter;
    float typewriter_delay;

    int text_length;
    int typewriter_position; 

  };
}
