/*
  ChoppingBoard for PoemCutter for experimental poetry recital game
  Matthew Carlin
  Copyright 2019
*/

#include "choppingboard.h"

using namespace std;
using namespace Honey;

void debug(int x) {
  printf("Here %d\n", x);
}

ChoppingBoard::ChoppingBoard(string file_pattern) {
  music = file_pattern;
}

void ChoppingBoard::initialize() {
  hot_config.checkAndUpdate();

  screen_width = hot_config.getInt("layout", "screen_width");
  screen_height = hot_config.getInt("layout", "screen_height");

  float sound_volume = hot_config.getFloat("sound", "sound_volume");
  sound.setSoundVolume(sound_volume);

  graphics.addImages("Art/", {
    "intro_screen",
    "blue_line",
    "grey_line",
    "green_line",
    "dull_green_line"
  });

  sound.addMusic(music, music + ".mp3");

  //time_since_music_start = 0;

  start_position = 0;

  printf("Using %s file set.\n", music.c_str());

  string line;

  playing_single_word = false;

  std::ifstream amplitude_file(music + ".amp");
  int count = 0;
  while (getline(amplitude_file, line)) {
    // std::vector<std::string> words;
    // boost::split(words, line, boost::is_any_of(","), boost::token_compress_on);
    float x = stof(line);
    if (count < 10) printf("%0.4f\n", x);
    amplitudes.push_back(x);
    count++;
  }

  std::ifstream word_file(music + ".txt");
  while (getline(word_file, line)) {
    std::vector<std::string> line_words;
    boost::split(line_words, line, boost::is_any_of(" "), boost::token_compress_on);
    for (string word : line_words) {
      if (word.length() > 0) {
        printf("%s\n", word.c_str());
        words.push_back(word);
      }
    }
  }

  chart_position_x = hot_config.getInt("layout", "amplitude_chart_position_x");
  chart_position_y = hot_config.getInt("layout", "amplitude_chart_position_y");
  pixel_scale = hot_config.getFloat("layout", "pixel_scale");
  threshold = hot_config.getFloat("algorithm", "threshold");
  width_of_silence = hot_config.getInt("algorithm", "width_of_silence");
  backtrack_to_silence = hot_config.getInt("algorithm", "backtrack_to_silence");

  marker_speed = 0.01;

  // string last = "under";
  // for (int i = 0; i < amplitudes.size(); i++) {
  //   string current = "under";
  //   if (amplitudes[i] > threshold) current = "over";
  //   if (current == "over" && last == "under") {
  //     locations.push_back(i);
  //   }
  //   last = current;
  // }

  int unders = 0;
  for (int i = 0; i < amplitudes.size(); i++) {
    if (amplitudes[i] < threshold) unders += 1;

    if (amplitudes[i] >= threshold && unders > width_of_silence) {
      locations.push_back(i);
      unders = 0;
    }
  }

  for (int l = 0; l < locations.size(); l++) {
    locations[l] -= backtrack_to_silence;
  }

  word_box = new Textbox(
    "Fonts/avenir_black.ttf",
    24,
    "X",
    (position) {10, 10},
    "#000000"
  );

  selected_item = 0;
}

void ChoppingBoard::logic() {
  if (input.anyKeyPressed()) {
    input.lockInput(0.1);
  }

  // if (input.keyDown("space")) {
  //   if (!sound.musicPlaying()) {
  //     float new_val = 0;
  //     while (new_val <= time_since_music_start - 5) {
  //       new_val += 5;
  //     }
  //     time_since_music_start = new_val;
  //     sound.playMusic(music, 1);
  //     sound.setMusicPosition(time_since_music_start);
  //     timing.mark("playing_music");
  //   } else {
  //     time_since_music_start += timing.since("playing_music");
  //     sound.stopMusic();
  //   }
  // }

  if (playing_single_word) {
    if (!sound.musicPlaying() 
      || (selected_item < locations.size() - 1 
          && locations[selected_item + 1] <= locations[selected_item] + timing.since("playing_music") * 100)) {
      sound.stopMusic();
      playing_single_word = false;
    }
  }

  if (!playing_single_word) {
    if (input.keyDown("w")) {
      playing_single_word = true;
      sound.playMusic(music, 1);
      sound.setMusicPosition(locations[selected_item] / 100.0);
      printf("Item %d\n", selected_item);
      printf("Location %d\n", locations[selected_item]);
      timing.mark("playing_music");
    }

    if (input.keyDown("space")) {
      if (!sound.musicPlaying()) {
        sound.playMusic(music, 1);
        sound.setMusicPosition(start_position);
        timing.mark("playing_music");
      } else {
        sound.stopMusic();
      }
    }

    if (input.keyDown("up")) {
      if (selected_item > 0) 
      {
        selected_item--;
        start_position = locations[selected_item] / 100.0;
      }
    }

    if (input.keyDown("down")) {
      if (selected_item < locations.size() - 2) {
        selected_item++;
        start_position = locations[selected_item] / 100.0;
      }
    }

    marker_speed *= 0.9;
    if (marker_speed < 0.01) marker_speed = 0.01;

    if (input.keyDown("left")) {
      start_position -= marker_speed;
      marker_speed += 0.01;
    }

    if (input.keyDown("right")) {
      start_position += marker_speed;
      marker_speed += 0.01;
    }

    if (input.keyDown("d")) {
      vector<int> new_locations = {};
      for (int l = 0; l < locations.size(); l++) {
        if (l != selected_item) {
          new_locations.push_back(locations[l]);
        }
      }
      locations = new_locations;

      if (selected_item > 0) {
        selected_item--;
      }
      start_position = locations[selected_item] / 100.0;
    }

    if (input.keyDown("a")) {
      vector<string> new_words = {};
      for (int w = 0; w < words.size(); w++) {
        if (w != selected_item + 1) {
          new_words.push_back(words[w]);
        } else {
          new_words[w-1] = new_words[w-1] + " " + words[w];
        }
      }
      words = new_words;
    }

    if (input.keyDown("s")) {
      std::ofstream output_file;
      output_file.open(music + ".split");

      for (int l = 0; l < locations.size(); l++) {
        string output = to_string(locations[l]);
        if (l < words.size()) {
          output += "; " + words[l];
        }
        output += "\n";
        output_file << output.c_str();
      }

      output_file.close();
      printf("Saved output to %s.split\n", music.c_str());
    }

    if (input.keyDown("m")) {
      locations.push_back(start_position * 100);
      sort(locations.begin(), locations.end());
      int closest = 4000;
      int choice = -1;
      for (int l = 0; l < locations.size(); l++) {
        if (abs(start_position * 100 - locations[l]) < closest) {
          closest = abs(start_position * 100 - locations[l]);
          choice = l;
        }
      }
      selected_item = choice;
      start_position = locations[selected_item] / 100.0;
    }
  }

  if (input.threeQuickKey("escape")) {
    screenmanager.setQuit();
  }
}

void ChoppingBoard::render() {
  // Clear the screen to a soft grey color
  graphics.clearScreen("#FFFFFF");
  graphics.setColor("#FFFFFF", 1.0);
  // Switch to 2D drawing mode
  graphics.draw2D();

  graphics.scale(pixel_scale, 1.0, 1.0);

  float time_location = start_position + timing.since("playing_music");
  if (!sound.musicPlaying()) {
    time_location = start_position;
  }

  int start = std::max((time_location * 100) - 200.0, 0.0);
  int end = std::min((time_location * 100) + 1200.0, amplitudes.size() + 0.0);
  //printf("%d, %d\n", start, end);
  for (int i = start; i < end; i++) {
    float height = amplitudes[i];
    graphics.drawImage("blue_line", chart_position_x + i - start, chart_position_y, false, 0, 1, height, 1);
    graphics.drawImage("blue_line", chart_position_x + i - start, chart_position_y - 100 * height, false, 0, 1, height, 1);
  }

  graphics.drawImage(
    "grey_line",
    chart_position_x + time_location * 100 - start,
    chart_position_y);
  graphics.drawImage(
    "grey_line",
    chart_position_x + time_location * 100 - start,
    chart_position_y - 100);

  //printf("Size %d\n", locations.size());
  for (int l = 0; l < locations.size(); l++) {
    if (locations[l] >= start && locations[l] <= end) {
      graphics.setColor("#FFFFFF", 1.0);
      string image = "green_line";
      if (l == selected_item) image = "dull_green_line";
      graphics.drawImage(
        image,
        chart_position_x + locations[l] - start,
        chart_position_y - 30);

      graphics.scale(1.0 / pixel_scale, 1.0, 1.0);
      if (l < words.size()) {
        word_box->setText(words[l]);
      } else {
        word_box->setText("X");
      }
      word_box->setPosition({(int) pixel_scale * (chart_position_x + locations[l] - start), chart_position_y - 200 + 30 * (l % 4)});
      word_box->setColor("#000000");
      if (l < locations.size() - 3) {
        if (time_location * 100 > locations[l] && time_location * 100 < locations[l+1]) {
          word_box->setColor("#FF0000");
        }
      } else {
        if (time_location * 100 > locations[l]) {
          word_box->setColor("#FF0000");
        }
      }
      word_box->draw();
      graphics.scale(pixel_scale, 1.0, 1.0);
    }
  }


  graphics.scale(1.0 / pixel_scale, 1.0, 1.0);
  word_box->setColor("#000000");
  word_box->setText(std::to_string((int) time_location));
  word_box->setPosition({40, 40});
  word_box->draw();
  word_box->setText(std::to_string((int) (start_position * 100)));
  word_box->setPosition({40, 80});
  word_box->draw();
  graphics.scale(pixel_scale, 1.0, 1.0);

}

ChoppingBoard::~ChoppingBoard() {

}