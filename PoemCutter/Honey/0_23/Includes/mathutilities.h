/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <math.h>
#include <string>
#include <stdlib.h>

#include "primitives.h"

using namespace std;
using namespace Honey;

namespace Honey {
  /*!
    The MathUtilities class provides math utility functions.

    http://www.friendsonmountains.com/blog/2018/08/28/lets-make-honey-version-0-15-sprites
  */
  class MathUtilities final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Time you're supposed to have.
    */
    static MathUtilities& instance();

    /*!
      Get a random integer between low and high (non-inclusive, eg 3,5 will return 3 or 4, not 5).
      
      @param low lowest value.
      @param high highest value.
      @returns a random number between the lowest and highest values.
    */
    int randomInt(int low, int high);

    /*!
      Get the distance between two positions.
      
      @param p1 a position.
      @param p2 a position.
      @returns distance between p1 and p2.
    */
    float distance(position p1, position p2);

    /*!
      Get the distance between two positions represented in floats.
      
      @param x1 first x coordinate.
      @param y1 first y coordinate.
      @param x2 second x coordinate.
      @param y2 second y coordinate.
      @returns distance between x1,y1 and x2,y2.
    */
    float distance(float x1, float y1, float x2, float y2);

    /*!
      Rotate a vector x,y by theta degrees counterclockwise.
      
      @param x x coordinate of the vector.
      @param y y coordinate of the vector.
      @param theta rotation angle in degrees. positive is counterclockwise.
      @returns a vector the same magnitude as x,y, rotated theta degrees from the origin.
    */
    point rotateVector(float x, float y, float theta);

    /*!
      For a line defined by p1 and p2 and a third point p3, get the closest point on the line.

      Note this may be outside the segment between p1 and p2.
      
      @param p1 a position.
      @param p2 a position.
      @param p3 a position.
      @returns the closest point on the line to p3
    */
    position closestPoint(position p1, position p2, position p3);

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    MathUtilities();
    ~MathUtilities();

    MathUtilities(const MathUtilities&) = delete;
    MathUtilities& operator=(const MathUtilities&) = delete;
    MathUtilities(MathUtilities&&) = delete;
    MathUtilities& operator=(MathUtilities&&) = delete;
  };

  extern MathUtilities& math_utils;
}
