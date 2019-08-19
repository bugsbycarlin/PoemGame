/*!
  @Honey
  @author Matthew Carlin
  Copyright 2018

  Shaders just holds Honey's vertex and fragment shaders as strings.
*/

#pragma once

#include <string>
#include <stdlib.h>

using namespace std;

namespace Honey {
  const string vertex_shader = R"(
  #version 330 core

  uniform mat4 mvp_matrix;

  layout(location = 0) in vec3 position_vector;
  layout(location = 1) in vec2 texture_vector;

  out vec2 fragment_texture_vector;

  void main(){
    gl_Position =  mvp_matrix * vec4(position_vector, 1);
    fragment_texture_vector = texture_vector;
  }
  )";

  const string fragment_shader = R"(
  #version 330 core

  uniform sampler2D texture_sampler;
  uniform vec4 color;

  in vec2 fragment_texture_vector;

  out vec4 final_color_vector;

  void main(){
    vec4 color_vector = color * texture(texture_sampler, fragment_texture_vector);

    if (color_vector.a <= 0.0001) {
      discard;
    }

    final_color_vector = color_vector;
  } 
  )";
}
