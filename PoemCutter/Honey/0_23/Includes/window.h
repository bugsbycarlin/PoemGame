/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <string>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <OpenGL/gl3.h>

using namespace std;

namespace Honey {
  /*!
    The Window class wraps SDL window creation.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/06/30/lets-make-honey-version-0-01-windows-and-libraries
  */
  class Window final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Window you're supposed to have.
    */
    static Window& instance();

    // The SDL window
    SDL_Window* window;

    // The OpenGL context
    SDL_GLContext context;

    int width;
    int height;

    /*!
      Initialize SDL, create a window, initialize OpenGL, initialize SDL images, sound, and fonts.
      
      @param title The title of the game.
      @param screen_width Self explanatory.
      @param screen_height Self explanatory.
      @param full_screen Self explanatory.
    */
    void initialize(string title, int screen_width, int screen_height, bool full_screen);

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    Window();
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;
  };

  extern Window& window;
}
