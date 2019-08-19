/*
  ChoppingBoard for PoemCutter for experimental poetry recital game
  Matthew Carlin
  Copyright 2019
*/

#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <map>
#include <string>

#include <math.h>
#include <boost/algorithm/string/split.hpp>

#include "honey.h"

#include "SDL2_mixer/SDL_mixer.h"

using namespace Honey;
using namespace std;

class ChoppingBoard {
 public:
  ChoppingBoard(string file_pattern);

  void initialize();

  void logic();
  void render();

  ~ChoppingBoard();

  string music;
  vector<string> words;
  vector<int> locations;
  vector<float> amplitudes;

  float threshold;

  float time_since_music_start;

  float start_position;

  int screen_width;
  int screen_height;

  int chart_position_x;
  int chart_position_y;
  float pixel_scale;

  int selected_item;

  bool playing_single_word;

  Textbox* word_box;
};