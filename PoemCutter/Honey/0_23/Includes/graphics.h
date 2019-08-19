/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <math.h>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "primitives.h"
#include "window.h"
#include "shaders.h"
#include "effects.h"

using namespace std;

namespace Honey {
  /*!
    The Graphics class class wraps OpenGL for drawing and handles image loading.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/08/lets-make-honey-version-0-02-set-up-opengl

    http://www.friendsonmountains.com/blog/2018/07/09/lets-make-honey-version-0-03-draw-something

    http://www.friendsonmountains.com/blog/2018/07/09/lets-make-honey-version-0-04-load-and-draw-images

    http://www.friendsonmountains.com/blog/2018/07/12/lets-make-honey-version-0-06-draw-caching

    http://www.friendsonmountains.com/blog/2018/07/21/lets-make-honey-version-0-10-starshine-the-graphics

    http://www.friendsonmountains.com/blog/2018/07/25/lets-make-honey-version-0-12-layouts-and-refactoring

    http://www.friendsonmountains.com/blog/2018/08/28/lets-make-honey-version-0-15-sprites
  */
  class Graphics final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Graphics you're supposed to have.
    */
    static Graphics& instance();

    /*!
      Effects Types.

      See graphs in http://www.friendsonmountains.com/blog/2018/07/14/lets-make-honey-version-0-07-effects
    */
    enum TWEEN_STYLES {
      LINEAR, /*!< Linear Tween. Constant speed. */
      SIGMOID, /*!< Sigmoid Tween. Starts slow, gets fast in the middle, ends slow. */
      CUBIC, /*!< Cubic Tween. Starts fast, pauses in the middle, ends fast. */
      RAMPDOWN, /*!< Rampdown Tween. Starts fast, ends slow. */
      RAMPUP, /*!< Rampdown Tween. Starts slow, ends fast. */
      SINEWAVE /*!< Sinewave Tween. Moves from start to end, then boomerangs back to start. */
    };

    /*!
      Initialize Graphics by performing OpenGL setup, including shaders, rendering pipeline, and model-view-control type stuff.
    */
    void initialize();

    /*!
      Store the current model matrix on the stack. This allows you to perform further transforms without losing your place.
    */
    void pushModelMatrix();

    /*!
      Pop a model matrix from the stack. This allows you to return to previous model configuration.
    */
    void popModelMatrix();

    /*!
      Perform a translation, which moves everything in the world by x, y, and z.
      
      @param x desired movement along the x axis.
      @param y desired movement along the y axis.
      @param z desired movement along the z axis.
    */
    void translate(float x, float y, float z);

    /*!
      Perform a rotation by the specified angle, around a vector defined by x, y, and z.
      
      @param angle desired rotation angle in degrees.
      @param x component of rotation vector.
      @param y component of rotation vector.
      @param z component of rotation vector.
    */
    void rotate(float angle, float x, float y, float z);

    /*!
      Perform a scale, rescaling everything in the world by x, y, and z proportions.
      
      @param x desired rescale along the x axis.
      @param y desired rescale along the y axis.
      @param z desired rescale along the z axis.
    */
    void scale(float x, float y, float z);

    /*!
      Return width of an image

      @param label the name of an image in our system. It is assumed this has already been loaded with addImage.
      @returns width of the label
    */
    int getWidth(string label);

    /*!
      Return height of an image

      @param label the name of an image in our system. It is assumed this has already been loaded with addImage.
      @returns height of the label
    */
    int getHeight(string label);

    /*!
      Parse a string color such as #FFD4C5 into a floatColor primitive.
      
      @param color a hex string color such as "#CF48FF".
      @returns floatColor, a struct which contains float values for Red, Green, and Blue from 0 to 1.
    */
    floatColor parseFloatColor(string color);

    /*!
      Parse a string color such as #FFD4C5 into an intColor primitive.
      
      @param color a hex string color such as "#CF48FF".
      @returns intColor, a struct which contains int values for Red, Green, and Blue from 0 to 255.
    */
    intColor parseIntColor(string color);

    /*!
      Set the global color of all subsequent draw operations on this draw cycle.
      
      @param color a hex string color such as "#CF48FF".
      @param opacity an opacity value from 0 (fully transparent) to 1 (opaque).
    */
    void setColor(string color, float opacity);

    /*!
      Set the global color of all subsequent draw operations on this draw cycle.
      
      @param r float value for red, from 0 (no red) to 1 (full red).
      @param g float value for green, from 0 (no green) to 1 (full green).
      @param b float value for blue, from 0 (no blue) to 1 (full blue).
      @param opacity an opacity value from 0 (fully transparent) to 1 (opaque).
    */
    void setColor(float r, float g, float b, float opacity);

    /*!
      Wipe the screen clean, setting everything to the specified color.
      
      @param color a hex string color such as "#CF48FF".
    */
    void clearScreen(string color);

    /*!
      Tell Graphics to prepare for 2D drawing. This sets orthographic perspective so that
      x and y correspond directly to the screen width and height (starting from 0,0 in
      the top left corner), and disabled depth testing so objects draw over each other
      based on draw order.
    */
    void draw2D();

    /*!
      Tell Graphics to use a particular layer value. By default this is zero.
      
      In 2d drawings, higher layers will draw in front of lower layers. In fact,
      graphics will just divide the layer by 100 and use this as the z value of the
      drawing. This works with transparency but does not work well with translucency.

      @param layer a float layer value.
    */
    void setLayer(float layer);

    /*!
      Tell Graphics to use the y position of every 2d drawing as the layer.

      In this case, items at the bottom of the screen are drawn in front of those higher up.
    */
    void usePositionBasedLayers();

    /*!
      Tell Graphics to use the draw order as de facto layering. This is the default.

      In this case, a later item will be drawn in front of an earlier item.

      The layer can be set manually with setLayer; within each manual layer,
      order will determine what's in front of that particular layer.
    */
    void useOrderBasedLayers();

    /*!
      Draw a 2D rectangle at the given x and y position with the given width and height.
      It is assumed that the color or texture (ie image) of the rectangle will have been
      set before this, either with setColor or setImage.
      
      @param desired x_position x coordinate of the rectangle on the screen.
      @param desired y_position y coordinate of the rectangle on the screen.
      @param desired width width of the rectangle on the screen.
      @param desired height height of the rectangle on the screen.
    */
    void drawRectangle(float x_position, float y_position, float width, float height);

    /*!
      Load an image at the specified path, storing it on the graphics card, where we
      can reference it later by using the specified label.
      
      @param label the label we will use to reference the image later (like "star").
      @param path the path to an image file on disk (like "Art/star.png").
    */
    void addImage(string label, string path);

    /*!
      Add many images to this system. Assumes png files under one root path.

      @param root_path OS valid path of a set of png files (eg "Art/"). Should have the slash.
      @param labels list of labels, each corresponding to a png file inside root_path (eg "star", "bear1", "bear2").
    */
    void addImages(string root_path, vector<string> labels);

    /*!
      Add an image from an existing SDL_Surface object, storing it on the graphics card, where we
      can reference it later by using the specified label.
      
      @param label the label we will use to reference the image later (like "star").
      @param image an SDL_Surface which represents an image in RAM.
    */
    void addImageFromSurface(string label, SDL_Surface* image);

    /*!
      Tell OpenGL we're using a particular image for the next round of drawing.
      
      @param label the name of an image in our system. It is assumed this has already been loaded with addImage.
    */
    void setImage(string label);

    /*!
      Draw an image at the given location.
      
      @param label the name of an image in our system. It is assumed this has already been loaded with addImage.
      @param x_position desired x coordinate of the image on the screen.
      @param y_position desired y coordinate of the image on the screen.
    */
    void drawImage(string label, int x_position, int y_position);

    /*!
      Draw an image at the given location. This version has more options; the image can be centered at x,y instead
      of drawn from the top left corner. It can be rotated clockwise by a specified angle, and scaled by a specified
      scale value.
      
      @param label the name of an image in our system. It is assumed this has already been loaded with addImage.
      @param x_position desired x coordinate of the image on the screen.
      @param y_position desired y coordinate of the image on the screen.
      @param centered whether to draw the image from the center instead of the top left.
      @param rotation desired clockwise rotation of the image on the screen in degrees.
      @param scale desired scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
    */
    void drawImage(
      string label,
      int x_position,
      int y_position,
      bool centered,
      float rotation,
      float scale);

    /*!
      Draw an image at the given location. This version has more options; the image can be centered at x,y instead
      of drawn from the top left corner. It can be rotated clockwise by a specified angle, and scaled by a specified
      scale value.
      
      @param label the name of an image in our system. It is assumed this has already been loaded with addImage.
      @param x_position desired x coordinate of the image on the screen.
      @param y_position desired y coordinate of the image on the screen.
      @param centered whether to draw the image from the center instead of the top left.
      @param rotation desired clockwise rotation of the image on the screen in degrees.
      @param x_scale desired x_scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
      @param y_scale desired x_scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
      @param z_scale desired x_scale of the image on the screen (1 is the original size, 0.5 is half size, 2 is double size, etc).
    */
    void drawImage(
      string label,
      int x_position,
      int y_position,
      bool centered,
      float rotation,
      float x_scale,
      float y_scale,
      float z_scale);


    /*!
      Remove the desired image from the graphics card and from this Graphics system.
      
      @param label the name of an image in our system. It is assumed this has already been loaded with addImage,
      but the system will merely warn if it can't find this image.
    */
    void removeImage(string label);

    /*!
      Remove all images, removing them from the graphics card and from this Graphics system.
    */
    void removeAllImages();

    /*!
      Check whether an image label exists in this Graphics system.
      
      @param label the name of an image in our system.
      @return true if and only if this label exists in the system, ie, it has been previously loaded with addImage and not removed.
    */
    bool checkImage(string label);

    /*!
      Update the display. Honey Graphics is double buffered, meaning on every cycle, everything is drawn to a hidden
      surface, and then when we call this method, the hidden surface and the visible surface are swapped, and the new
      stuff suddenly appears on the screen all together.
    */
    void updateDisplay();

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    Graphics();
    ~Graphics();

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    Graphics(Graphics&&) = delete;
    Graphics& operator=(Graphics&&) = delete;

    // Pointers to buffers for stuff on the graphics card
    unordered_map<string, GLuint> vertex_buffers;
    GLuint rectangle_texture_buffer;
    GLuint vertex_array_id;

    // Maps to store texture information
    map<string, GLuint> texture_map;
    map<string, int> texture_widths;
    map<string, int> texture_heights;

    // Variables for communicating with the graphics card
    GLuint mvp_matrix_id;
    GLuint color_id;
    GLuint texture_sampler_id;
    GLuint shader_program;

    // Variables for working on the CPU side
    glm::mat4 projection;
    glm::mat4 model;
    glm::vec4 color;
    bool using_2d;
    bool using_y_position_as_layer;
    float layer;
    vector<glm::mat4> model_stack;

    void initializeOpenGL();
    void initializeBuffersAndGeometry();
    void initializeShaders();

    void cacheRectangle(float width, float height);

    float draw_counter;
  };

  extern Graphics& graphics;
}
