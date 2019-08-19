/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <chrono>
#include <functional>
#include <string>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Honey {
  /*!
    The Timing class provides time logic convenience functions.

    Different functions are all referenced by string labels; these labels are shared across functions.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/11/lets-make-honey-version-0-05-basic-controls

    http://www.friendsonmountains.com/blog/2018/08/28/lets-make-honey-version-0-15-sprites

    http://www.friendsonmountains.com/blog/2018/09/20/lets-make-honey-version-0-16-sequences
  */
  class Timing final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of Timing you're supposed to have.
    */
    static Timing& instance();

    /*!
      Remove a label from this system.
      
      @param label Name of the label.
    */
    void remove(string label);

    /*!
      Check if a label exists.
      
      @param label Name of the label.
      @returns true if and only if the label exists in this system.
    */
    bool check(string label);

    /*!
      Mark the current time for this label.
      
      @param label Name of the label.
    */
    void mark(string label);

    /*!
      Store a duration time in seconds for this label.
      
      @param label Name of the label.
      @param seconds Intended duration in seconds.
    */
    void setDuration(string label, float seconds);

    /*!
      Get the time in seconds since this label was marked.
      
      @param label Name of the label.
      @returns the time since this label was last marked.
    */
    float since(string label);

    /*!
      Get the intended duration in seconds of this label.
      
      @param label Name of the label.
      @returns duration of the label.
    */
    float duration(string label);

    /*!
      Lock this label for this many seconds. Calls to locked will now return true.
      
      @param label Name of the label.
      @param seconds the duration of the lock.
    */
    void lock(string label, float seconds);

    /*!
      Check whether a label has been time locked.
      
      @param label Name of the label.
      @returns true if and only if the label has been locked using makeTimeLock, less than a certain number of seconds ago.
    */
    bool locked(string label);

    /*!
      Override the global time value to force a particular time.
      
      @param float Time in seconds.
    */
    void setOverrideTime(float seconds);

    /*!
      Remove the global time override, returning to the system clock.
      
      @param float Time in seconds.
    */
    void removeOverrideTime();

    /*!
      Pause all existing time counters. New ones will run as normal.

      Pausing is a stack; if there are three counters, A, B and C, and pause
      is called, these three counters will be paused. If counter D is created,
      it will run as normal. If pause is called again, D will also be paused.
      If unpause is called, D will be unpaused. If unpause is called again,
      A, B and C will be unpaused. This is to allow the running of timers
      during a game's pause state, for instance for pause animations.

      See Tests/Pausing for a demonstration.
    */
    void pause();

    /*!
      Unpause the counters that were paused on the last pause.
    */
    void unpause();

    /*!
      Make an integer counter for this label that lasts for this many seconds.
      
      @param label Name of the label.
      @param seconds the duration of the counter.
    */
    void makeTransientCounter(string label, float seconds);

    /*!
      If this label still has a counter associated with it, increment that counter.
      
      @param label Name of the label.
      @param value How much to add to the counter.
    */
    void incrementTransientCounter(string label, int value);

    /*!
      Get the value of a transient counter, or 0 if it's expired or invalid.
      
      @param label Name of the label.
      @returns the value of the counter.
    */
    int transientCounterValue(string label);

    /*!
      Make a timed sequence.

      This will count up from zero, delaying each increment by the next timing value in the sequence.

      For instance, if the timing {0.5, 1.0, 0.5} is supplied, the counter will start at 0,
      increment to 1 after 0.5 seconds, increment to 2 after 0.5+1.0 seconds, and increment
      to 3 after 0.5+1.0+0.5 seconds.
      
      @param label Name of the label.
      @param sequence_timing list of delays between increments.
    */
    void makeSequence(string label, vector<float> sequence_timing);

    /*!
      Get the value of a timed sequence.

      For instance, if the timing {0.5, 1.0, 0.5} was supplied during creation,
      at any time before 0.5 seconds, this method will return 0, at any time between 0.5 and
      1.5 seconds, this method will return 1, at any time between 1.5 seconds and 2.0 seconds,
      this method will return 2, and at any time after 2.0 seconds this method will return 3.

      If the label doesn't exist, this method will return 0.

      @param label Name of the label.
    */
    int sequenceValue(string label);

    /*!
      Make a timed sequence with a function to perform actions.

      This will make a sequence, the same as makeSequence. It will also attach a function pointer
      to that sequence; calls to doSequence will call that function with the current sequence value
      and current timing value as parameters.
      
      @param label Name of the label.
      @param sequence_timing list of delays between increments.
      @param action std::function, void(int, float), which takes sequence value and sequence timing as parameters.
    */
    void makeSequenceWithFunction(string label, vector<float> sequence_timing, function<void(int, float)> action);

    /*!
      Use a timed sequence to perform actions at desired moments in time.

      This method presumes an action has been attached using makeSequenceWithFunctions (and returns if none is found).

      When each new sequence value is reached, this method fires the action method *one time*.
      The duration of the final action (called when the full sequence is complete) is 0.

      For instance, if the timing {0.5, 1.0, 0.5} is applied, this method
      will call action(0, 0.5) immediately,
      will call action(1, 1.0) after 0.5 seconds,
      will call action(2, 0.5) after 1.5 seconds,
      will call action(3, 0.0) after 2.0 seconds.

      @param label Name of the label.
    */
    void doSequence(string label);

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    Timing();
    ~Timing();

    Timing(const Timing&) = delete;
    Timing& operator=(const Timing&) = delete;
    Timing(Timing&&) = delete;
    Timing& operator=(Timing&&) = delete;

    // Time getter; checks for override, then uses system clock
    unsigned long getTime();

    unordered_map<string, unsigned long> time_markers;
    unordered_map<string, float> duration_markers;
    unordered_map<string, int> pause_values;

    unordered_map<int, float> pause_history;

    unordered_map<string, int> transient_counter_values;

    unordered_map<string, vector<float>> sequence_timings;
    unordered_map<string, int> sequence_counters;
    unordered_map<string, function<void(int, float)>> sequence_actions;

    bool time_from_override;
    float time_override;
    int pause_counter;
  };

  extern Timing& timing;
}
