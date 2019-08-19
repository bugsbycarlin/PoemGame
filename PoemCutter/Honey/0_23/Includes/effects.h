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

#include "timing.h"

using namespace std;

namespace Honey {
  /*!
    The Effects class provides convenience methods to create visual effects.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/14/lets-make-honey-version-0-07-effects

    http://www.friendsonmountains.com/blog/2018/08/31/lets-make-honey-version-0-15-sprites
  */
  class Effects final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Effects you're supposed to have.
    */
    static Effects& instance();

    /*!
      Effects Styles.

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

    enum STATE {
      WAITING,
      BUSY,
      FINISHED
    };

    /*!
      Start the effect!

      @param label The effect you want to start.
    */
    void start(string label);

    /*!
      Stop the effect!

      @param label The effect you want to stop.
    */
    void stop(string label);

    /*!
      Check whether an effect is waiting.

      @param label The effect you want to check.
      @return true if and only if the label exists and the state is waiting.
    */
    bool waiting(string label);

    /*!
      Check whether an effect is busy.

      @param label The effect you want to check.
      @return true if and only if the label exists and the state is busy.
    */
    bool busy(string label);

    /*!
      Check whether an effect is finished.
      
      @param label The effect you want to check.
      @return true if and only if the label exists and the state is finished.
    */
    bool finished(string label);

    /*!
      Remove an effect.
      @param label The effect you want to remove.
    */
    void remove(string label);

    /*!
      Remove all effects currently stored in the Effects instance.
    */
    void removeAllEffects();

    /*!
      Create a tween which interpolates between two values over time.
      
      @param label Name of the effect to create.
      @param start_value The value when the tween starts.
      @param end_value The value when the tween ends.
      @param duration_in_seconds The duration of the tween effect.
    */
    void makeTween(string label, float start_value, float end_value, float duration_in_seconds);

    /*!
      Get the interpolated value of a given tween effect.

      Note that time is calculated for you in the background.
      
      @param label Name of the effect.
      @param style Tween style (see TWEEN_STYLES enum for different styles).
      @return A value somewhere between the start and end values for this tween.
    */
    float tween(string label, int style);

    /*!
      Create a shake effect which adds some random noise.
      
      @param label Name of the effect to create.
      @param shake_size Shake noise is sampled from the range (-shake_size, shake_size).
      @param duration_in_seconds The duration of the shake effect.
    */
    void makeShake(string label, int shake_size, float duration_in_seconds);

    /*!
      Grab a value from the random shaker.

      This value will range from -shake_size to shake_size.
      
      @param label Name of the effect.
      @return A value in the range (-shake_size, shake_size) as defined in makeShake.
    */
    float shake(string label);

    /*!
      Create an oscillation effect, which goes back and forth in a sine wave.

      @param label Name of the effect to create.
      @param oscillation_size Effect ranges from (-oscillation_size, oscillation_size).
      @param period_in_seconds A full oscillation is completed every period_in_seconds.
    */
    void makeOscillation(string label, float oscillation_size, float period_in_seconds);

    /*!
      Grab a value from the random shaker.

      This value will range from -oscillation_size to oscillation_size.

      Note that time is calculated for you in the background.
      
      @param label Name of the effect.
      @return A value in the range (-oscillation_size, oscillation_size) as defined in makeOscillation.
    */
    float oscillation(string label);

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    Effects();
    ~Effects();

    Effects(const Effects&) = delete;
    Effects& operator=(const Effects&) = delete;
    Effects(Effects&&) = delete;
    Effects& operator=(Effects&&) = delete;

    const float sigmoid_steepness = 5;

    unordered_map<string, int> state;
    unordered_map<string, float> start_value;
    unordered_map<string, float> end_value;
    unordered_map<string, float> size;
  };

  extern Effects& effects;
}
