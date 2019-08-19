/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018
*/

#pragma once

#include <string>
#include <stdlib.h>
#include <unordered_map>

#include "tinyxml/tinyxml2.h"

#include "timing.h"

using namespace std;

namespace Honey {
  /*!
    The HotConfig class reads config from a file and can update during runtime.

    Configs are expected to be light xml-like, organized into sections, with bool,
    int, float, or string values. Example config doesn't look good in doxygen;
    please see blog post.

    Primarily covered in blog posts:

    http://www.friendsonmountains.com/blog/2018/07/14/lets-make-honey-version-0-08-honey-hot-config
  */
  class HotConfig final {
   public:
    /*!
      Singleton instance getter.

      @return This'll get you the one instance of HotConfig you're supposed to have.
    */
    static HotConfig& instance();

    /*! HotConfig status. */
    enum STATUS {
      SUCCESS, /*!< Success. */
      FAILURE, /*!< Failure to update. */
      SLEEPING, /*!< Sleeping. HotConfig sleeps for a few seconds between updates. */
    };

    /*!
      Change the path of the config file. It's "config.txt" by default.
      
      @param path OS Compatible path to a config file.
    */
    void setPath(string path);

    /*!
      Change the interval between updates. It's 2 seconds by default.
      
      @param interval Time between updates, in seconds.
    */
    void setUpdateInterval(float interval);

    /*!
      Check if enough time has passed, and if so, reload the config.
      
      @return int Status code: SUCCESS, FAILURE, or SLEEPING.
    */
    int checkAndUpdate();

    /*!
      Reload the config without checking time.
      
      @return int Status code: SUCCESS, FAILURE, or SLEEPING.
    */
    int update();

    /*!
      Get a boolean value from config.
      
      @param section Config section.
      @param name Value name.
      @return bool The value. Default is false.
    */
    bool getBool(string section, string name);

    /*!
      Get a int value from config.
      
      @param section Config section.
      @param name Value name.
      @return int The value. Default is 0.
    */
    int getInt(string section, string name);

    /*!
      Get a float value from config.
      
      @param section Config section.
      @param name Value name.
      @return float The value. Default is 0.
    */
    float getFloat(string section, string name);

    /*!
      Get a string value from config.
      
      @param section Config section.
      @param name Value name.
      @return string The value. Default is the empty string.
    */
    string getString(string section, string name);

   private:
    // Hide constructor, destructor, copy constructor and assignment operator
    HotConfig();
    ~HotConfig();

    HotConfig(const HotConfig&) = delete;
    HotConfig& operator=(const HotConfig&) = delete;
    HotConfig(HotConfig&&) = delete;
    HotConfig& operator=(HotConfig&&) = delete;

    const float default_update_interval = 2;
    float update_interval;

    const string default_path = "config.txt";
    string path;

    unordered_map<string, unordered_map<string, bool>> bools = {};
    unordered_map<string, unordered_map<string, int>> ints = {};
    unordered_map<string, unordered_map<string, float>> floats = {};
    unordered_map<string, unordered_map<string, string>> strings = {};
  };

  extern HotConfig& hot_config;
}
