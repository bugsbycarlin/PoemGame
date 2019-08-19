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
#include <unordered_map>

// Honey includes
#include "primitives.h"

using namespace std;

namespace Honey {
  /*!
    The LayoutSettings struct holds configuration parameters for a particular layout.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/25/lets-make-honey-version-0-12-layouts-and-refactoring
  */
  struct LayoutSettings {
    int x;
    int y;
    int x_margin;
    int y_margin;
    int num_per_row;
  };

  /*!
    The Layouts class has convenience methods for creating simple visual layouts.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/25/lets-make-honey-version-0-12-layouts-and-refactoring

    <pre>
    Types of layouts:
    
    Row layout: Looks like a 1d array of items in a single row.
    Access: value
    1  2  3  4  5  6  7  8  9  10
    
    
    Column layout: Looks like a 1d array of items in a single column.
    Access: value
    1
    2
    3
    4
    
    
    Tile layout: A two dimensional grid or tile layout for a two dimensional set of elements.
    Access: col_value, row_value
    1,1  1,2  1,3  1,4  1,5 ...
    2,1  2,2  2,3  2,4  2,5 ...
    3,1  3,2  3,3  3,4  3,5 ...
    

    TileWrap layout: A two dimensional grid or tile layout for a one dimensional set of elements
    which wraps around based on the value of num_per_row
    Access: value
    If num_per_row is 4:
    1  2  3  4
    5  6  7  8
    9  10 11 12
    13 14 15 16
    
    
    Stagger layout: Looks like the stars in an american flag, with every
    other row indented by half margin.
    Access: col_value, row_value
    1,1  1,2  1,3  1,4  1,5 ...
       2,1  2,2  2,3  2,4  2,5 ...
    3,1  3,2  3,3  3,4  3,5 ...
       4,1  4,2  4,3  4,4  4,5
    

    StaggerWrap layout: Items wrap based on num_per_row, but every other
    row is indented and has one less item.
    Access: value
    If num_per_row is 5:
    1   2   3   4   5
      6   7   8   9
    10  11  12  13  14
      15  16  17  18
    </pre>
    
  */
  class Layouts final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Layouts you're supposed to have.
    */
    static Layouts& instance();

    /*!
      Create a single row layout.
      
      @param label Name of the layout.
      @param x horizontal position of the first (or top left) element of the layout.
      @param y vertical position of the first (or top left) element of the layout.
      @param x_margin horizontal gap in pixels between elements.
    */
    void makeRowLayout(string label, int x, int y, int x_margin);

    /*!
      Create a single column layout.
      
      @param label Name of the layout.
      @param x horizontal position of the first (or top left) element of the layout.
      @param y vertical position of the first (or top left) element of the layout.
      @param y_margin vertical gap in pixels between elements.
    */
    void makeColumnLayout(string label, int x, int y, int y_margin);

    /*!
      Create a two dimensional grid or tile layout for a two dimensional set of elements.
      
      @param label Name of the layout.
      @param x horizontal position of the first (or top left) element of the layout.
      @param y vertical position of the first (or top left) element of the layout.
      @param x_margin horizontal gap in pixels between elements.
      @param y_margin vertical gap in pixels between elements.
    */
    void makeTileLayout(string label, int x, int y, int x_margin, int y_margin);

    /*!
      Create a two dimensional grid or tile layout for a one dimensional set of elements by wrapping around.
      
      @param label Name of the layout.
      @param x horizontal position of the first (or top left) element of the layout.
      @param y vertical position of the first (or top left) element of the layout.
      @param x_margin horizontal gap in pixels between elements.
      @param y_margin vertical gap in pixels between elements.
      @param num_per_row how many elements in a row before wrapping around to the next row.
    */
    void makeTileWrapLayout(string label, int x, int y, int x_margin, int y_margin, int num_per_row);

    /*!
      Create a two dimensional staggered layout for a two dimensional set of elements.
      
      @param label Name of the layout.
      @param x horizontal position of the first (or top left) element of the layout.
      @param y vertical position of the first (or top left) element of the layout.
      @param x_margin horizontal gap in pixels between elements.
      @param y_margin vertical gap in pixels between elements.
    */
    void makeStaggerLayout(string label, int x, int y, int x_margin, int y_margin);

    /*!
      Create a two dimensional staggered layout for a one dimensional set of elements by wrapping around.
      
      @param label Name of the layout.
      @param x horizontal position of the first (or top left) element of the layout.
      @param y vertical position of the first (or top left) element of the layout.
      @param x_margin horizontal gap in pixels between elements.
      @param y_margin vertical gap in pixels between elements.
      @param num_per_row how many elements in a row before wrapping around to the next row.
    */
    void makeStaggerWrapLayout(string label, int x, int y, int x_margin, int y_margin, int num_per_row);

    /*!
      Get the screen position of an element in a row layout.
      
      @param label Name of the layout.
      @param element_number The element number.
      @returns a position primitive which holds x and y screen coordinates.
    */
    position row(string label, int element_number);

    /*!
      Get the screen position of an element in a column layout.
      
      @param label Name of the layout.
      @param element_number The element number.
      @returns a position primitive which holds x and y screen coordinates.
    */
    position column(string label, int element_number);

    /*!
      Get the screen position of an element in a tile layout.
      
      @param label Name of the layout.
      @param column_number The column number.
      @param row_number The row number.
      @returns a position primitive which holds x and y screen coordinates.
    */
    position tile(string label, int column_number, int row_number);

    /*!
      Get the screen position of an element in a tile wrap layout.
      
      @param label Name of the layout.
      @param element_number The element number.
      @returns a position primitive which holds x and y screen coordinates.
    */
    position tileWrap(string label, int element_number);

    /*!
      Get the screen position of an element in a staggered tile layout.
      
      @param label Name of the layout.
      @param column_number The column number.
      @param row_number The row number.
      @returns a position primitive which holds x and y screen coordinates.
    */
    position stagger(string label, int column_number, int row_number);

    /*!
      Get the screen position of an element in a staggered tile wrap layout.
      
      @param label Name of the layout.
      @param element_number The element number.
      @returns a position primitive which holds x and y screen coordinates.
    */
    position staggerWrap(string label, int element_number);

    /*!
      Remove a layout from this system.
      
      @param label Name of the layout.
    */
    void remove(string label);

   private:
    Layouts();
    ~Layouts();

    Layouts(const Layouts&) = delete;
    Layouts& operator=(const Layouts&) = delete;
    Layouts(Layouts&&) = delete;
    Layouts& operator=(Layouts&&) = delete;

    unordered_map<string, LayoutSettings> settings;
  };

  extern Layouts& layouts;
}
