/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <string>
#include <stdlib.h>
#include <unordered_map>

// Honey includes
#include "screen.h"

using namespace std;

namespace Honey {
  /*!
    The ScreenManager class manages a series of screens.

    ScreenManager is meant to be almost the only object used by the main game loop. It has
    an unordered_map of unique_ptrs of screens. You can add a screen by label. You can delete
    a screen by label. You can set the current screen, and get the label of the current screen.
    You can tell the current screen to initialize, or run an iteration of the game loop.
    ScreenManager also has a quit boolean, and you can tell it to quit.

    These features are meant to allow a user to write a game loop which is agnostic to whichever
    game screen is currently running, and even which other ones exist.

    You could either write a loop which checks conditions, creates and initializes new game screens,
    changes screens if necessary, and then loops on the current game screen.

    Or, you could let the screens create each other (and add each other to the screen manager)
    and just run a loop on the current game screen, quitting if the manager ever gets a quit signal.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/09/21/lets-make-honey-version-0-17-screens
  */
  class ScreenManager final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of ScreenManager you're supposed to have.
    */
    static ScreenManager& instance();

    /*!
      Add a screen to the manager.
      
      @param label The desired label for referencing the screen.
      @param screen unique_ptr to a screen.
    */
    void addScreen(string label, unique_ptr<Screen> &screen);

    /*!
      Delete a screen from the manager.
      
      @param label The desired label for referencing the screen.
    */
    void deleteScreen(string label);

    /*!
      Check the existence of a screen.
      
      @param label The desired label for referencing the screen.
    */
    bool checkScreen(string label);

    /*!
      Set the current screen.
      
      @param label The label of the current screen.
    */
    void setCurrentScreen(string label);

    /*!
      Get the current screen.
      
      @returns The label of the current screen.
    */
    string getCurrentScreen();

    /*!
      Call initialize on the current screen (if it's not the empty string).
    */
    void initialize();

    /*!
      Call loop on the current screen (if it's not the empty string).
    */
    void loop();

    /*!
      Set the quit variable.
    */
    void setQuit();

    /*!
      Get the quit variable.

      @returns true if quit status is true.
    */
    bool getQuit();

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    ScreenManager();
    ~ScreenManager();

    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
    ScreenManager(ScreenManager&&) = delete;
    ScreenManager& operator=(ScreenManager&&) = delete;

    unordered_map<string, unique_ptr<Screen>> screens;

    bool quit_status;
    string current_screen;
  };

  extern ScreenManager& screenmanager;
}
