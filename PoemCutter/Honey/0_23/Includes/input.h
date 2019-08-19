/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <string>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "primitives.h"
#include "timing.h"

using namespace std;

namespace Honey {
  /*!
    The Input class wraps SDL input methods to create an event handling system.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/11/lets-make-honey-version-0-05-basic-controls

    There is a key map which allows you to use short string names instead of SDL constants:

    @param SDLK_UP up
    @param SDLK_DOWN down
    @param SDLK_RIGHT right
    @param SDLK_LEFT left
    @param SDLK_BACKSPACE backspace
    @param SDLK_TAB tab
    @param SDLK_SPACE space
    @param SDLK_ESCAPE escape
    @param SDLK_RETURN return
    @param SDLK_DELETE delete
    @param SDLK_BACKSLASH backslash
    @param SDLK_QUOTE quote
    @param SDLK_QUOTEDBL doublequote
    @param SDLK_PLUS +
    @param SDLK_COMMA ","
    @param SDLK_MINUS -
    @param SDLK_PERIOD .
    @param SDLK_SLASH /
    @param SDLK_COLON :
    @param SDLK_SEMICOLON ;
    @param SDLK_LESS <
    @param SDLK_EQUALS =
    @param SDLK_GREATER >
    @param SDLK_QUESTION ?
    @param SDLK_AT @
    @param SDLK_LEFTBRACKET [
    @param SDLK_RIGHTBRACKET ]
    @param SDLK_CARET ^
    @param SDLK_UNDERSCORE _
    @param SDLK_EXCLAIM !
    @param SDLK_HASH #
    @param SDLK_DOLLAR $
    @param SDLK_PERCENT %
    @param SDLK_AMPERSAND &
    @param SDLK_LEFTPAREN (
    @param SDLK_RIGHTPAREN )
    @param SDLK_ASTERISK *
    @param SDLK_LCTRL left_control
    @param SDLK_RCTRL right_control
    @param SDLK_LALT left_alt
    @param SDLK_RALT right_alt
    @param SDLK_LSHIFT left_shift
    @param SDLK_RSHIFT right_shift
    @param SDLK_LGUI left_command
    @param SDLK_RGUI right_command
    @param SDLK_0 0
    @param SDLK_1 1
    @param SDLK_2 2
    @param SDLK_3 3
    @param SDLK_4 4
    @param SDLK_5 5
    @param SDLK_6 6
    @param SDLK_7 7
    @param SDLK_8 8
    @param SDLK_9 9
    @param SDLK_KP_0 0
    @param SDLK_KP_1 1
    @param SDLK_KP_2 2
    @param SDLK_KP_3 3
    @param SDLK_KP_4 4
    @param SDLK_KP_5 5
    @param SDLK_KP_6 6
    @param SDLK_KP_7 7
    @param SDLK_KP_8 8
    @param SDLK_KP_9 9
    @param SDLK_a a
    @param SDLK_b b
    @param SDLK_c c
    @param SDLK_d d
    @param SDLK_e e
    @param SDLK_f f
    @param SDLK_g g
    @param SDLK_h h
    @param SDLK_i i
    @param SDLK_j j
    @param SDLK_k k
    @param SDLK_l l
    @param SDLK_m m
    @param SDLK_n n
    @param SDLK_o o
    @param SDLK_p p
    @param SDLK_q q
    @param SDLK_r r
    @param SDLK_s s
    @param SDLK_t t
    @param SDLK_u u
    @param SDLK_v v
    @param SDLK_w w
    @param SDLK_x x
    @param SDLK_y y
    @param SDLK_z z
  */
  class Input final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Input you're supposed to have.
    */
    static Input& instance();

    /*!
      Process all SDL input events which have occured since the last time this was called.
    */
    void processInput();

    /*!
      Lock all input for a period of time. All input commands will return negative or zero.
      
      @param duration_in_seconds The duration of the global input lock.
    */
    void lockInput(float duration_in_seconds);

    /*!
      Unlock all input, canceling the global input lock.
    */
    void unlockInput();

    /*!
      Return true if the input is currently globally locked.

      @return true if the input is currently globally locked.
    */
    bool locked();

    /*!
      Count the number of times this key was pressed.
      
      @param key The short string name for a keyboard key.
      @return the number if times this key was pressed
    */
    int keyPressed(string key);

    /*!
      Was this key held down?
      
      @param key The short string name for a keyboard key.
      @return true if and only if this key was held down.
    */
    bool keyDown(string key);

    /*!
      Was this key released?
      
      @param key The short string name for a keyboard key.
      @return true if and only if this key was released.
    */
    bool keyUp(string key);

    /*!
      Convenience method. Was this key pressed three times in a one second interval?
      
      @param key The short string name for a keyboard key.
      @return true if and only if this key was pressed three times in a one second interval.
    */
    bool threeQuickKey(string key);

    /*!
      Convenience method. Was any key pressed?
      
      @return true if and only if any key was pressed.
    */
    bool anyKeyPressed();

    /*!
      Count the number of times this action was performed.
      
      @param action The name of an action.
      @return the number if times this action was performed
    */
    int actionPressed(string action);

    /*!
      Was this action held down?
      
      @param action The name of an action.
      @return true if and only if this action was held down.
    */
    bool actionDown(string action);

    /*!
      Was this action released?
      
      @param action The name of an action.
      @return true if and only if this action was released.
    */
    bool actionUp(string action);

    /*!
      Convenience method. Was this action performed three times in a one second interval?
      
      @param action The name of an action.
      @return true if and only if this action was performed three times in a one second interval.
    */
    bool threeQuickAction(string action);

    /*!
      Connect a key to an action. Hereafter, if this key is used (pressed, down, or released),
      this action will also be used.
      
      @param action The name of an action.
      @param key The short string name for a key.
    */
    void addActionKey(string action, string key);

    /*!
      Remove or de-register an action from this system.
      
      @param action The name of an action.
    */
    void removeAction(string action);

    /*!
      Get a list of mouseEvents since the last processInput.

      The list is in time order. Each event is a string button, a string action, and x, y coordinates.

      Example list:
      left, down, 100, 100
      none, move, 110, 100
      none, move, 110, 110
      left, up, 110, 110
      
      @return vector of mouseEvents.
    */
    vector<mouseEvent> getMouseEvents();

   private:
    Input();
    ~Input();

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;

    const string global_input_lock = "__global_input_lock__";

    unordered_map<string, string> action_to_key;

    vector<mouseEvent> mouse_events;

    unordered_map<string, bool> down;
    unordered_map<string, bool> up;
    unordered_map<string, int> pressed;

    string translateToKey(SDL_Event event);
  };

  extern Input& input;
}
