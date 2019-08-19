/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018

  Primitives has some useful structs and typedefs that get usefully used all over this place.
*/

#pragma once

#include <string>
#include <unordered_map>
#include <boost/variant.hpp>

using namespace std;

namespace Honey {
  /*!
    position holds integer screen coordinates x and y.
  */
  struct position {
    int x;
    int y;

    bool operator<(const position & pos) const {
      return y < pos.y;
    }
  };

  const position origin = {0, 0};

  /*!
    point holds float space coordinates x, y, and z.
  */
  struct point {
    float x;
    float y;
    float z;
  };

  /*!
    floatColor holds float color values r, g, and b which should be between 0 and 1.
  */
  struct floatColor {
    float r;
    float g;
    float b;
  };

  /*!
    intColor holds int color values r, g, and b which should be between 0 and 255.
  */
  struct intColor {
    int r;
    int g;
    int b;
  };

  /*!
    box holds a two dimensional box shape.
  */
  struct box {
    float top;
    float left;
    float bottom;
    float right;
  };

  /*!
    mouseEvent holds a single mouse event, comprised of two strings and two coordinates.

    Examples:
    left, down, 100, 100
    none, move, 110, 100
    none, move, 110, 110
    left, up, 110, 110
  */
  struct mouseEvent {
    string button;
    string event;
    int x;
    int y;
  };

  /*!
    <pre>
    \typdef settings is a cheap way to build settings dictionaries like
      settings s = {
      {"type", "tween"},
      {"style", "sigmoid"},
      {"label", "bear_movement"},
      {"active", 0},
      {"start", 1},
      {"end", 0},
      {"duration", 1.5}}
    </pre>
  */
  typedef boost::variant<int, double, string> primitive;
  typedef unordered_map<string, primitive> settings;
}
