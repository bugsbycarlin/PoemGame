/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <chrono>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <unordered_map>

#include "primitives.h"
#include "mathutilities.h"

using namespace std;

namespace Honey {
  /*!
    The Collisions class provides methods to detect collisions between different types of objects.

    Primarily covered in blog posts:

    X
  */
  class Collisions final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Collisions you're supposed to have.
    */
    static Collisions& instance();

    /*!
      Test for a collision between box b1 (offset by position p1) and box b2 (offset by position p2)

      @param p1 a 2d position
      @param b1 a box whose coordinates are offset by p1
      @param p2 a 2d position
      @param b2 a box whose coordinates are offset by p2

      @return True if and only if the boxes overlap
    */
    bool test(position p1, box b1, position p2, box b2);

    /*!
      Test for a collision between box b1 (offset by position p1) and a line between p2 and p3

      @param p1 a 2d position
      @param b1 a box whose coordinates are offset by p1
      @param p2 a 2d position
      @param p3 a 2d position

      @return True if and only if the box overlaps the line
    */
    bool test(position p1, box b1, position p2, position p3);

    /*!
      Test for a collision between a circle of radius r1 centered at p1 and a circle of radius r2 centered at p2

      @param p1 a 2d position
      @param r1 the radius of the object at p1
      @param p2 a 2d position
      @param r2 the radius of the object at p2

      @return True if and only if the circles overlap
    */
    bool test(position p1, float r1, position p2, float r2);

    /*!
      Test for a collision between a circle of radius r1 centered at p1 and box b2 (offset by position p2)

      @param p1 a 2d position
      @param r1 the radius of the object at p1
      @param p2 a 2d position
      @param b2 a box whose coordinates are offset by p2

      @return True if and only if the circle overlaps the box
    */
    bool test(position p1, float r1, position p2, box b2);

    /*!
      Test for a collision between a circle of radius r1 centered at p1 and a line between p2 and p3

      @param p1 a 2d position
      @param r1 the radius of the object at p1
      @param p2 a 2d position
      @param p3 a 2d position

      @return True if and only if the circle overlaps the line
    */
    bool test(position p1, float r1, position p2, position p3);

    /*!
      Test for a collision between a line between p1 and p2 and a line between p3 and p4

      @param p1 a 2d position
      @param p2 a 2d position
      @param p3 a 2d position
      @param p4 a 2d position

      @return True if and only if the lines overlap
    */
    bool test(position p1, position p2, position p3, position p4);

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    Collisions();
    ~Collisions();

    Collisions(const Collisions&) = delete;
    Collisions& operator=(const Collisions&) = delete;
    Collisions(Collisions&&) = delete;
    Collisions& operator=(Collisions&&) = delete;
  };

  extern Collisions& collisions;
}
