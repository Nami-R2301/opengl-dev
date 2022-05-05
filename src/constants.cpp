//
// Created by nami on 4/28/22.
//
#include <iostream>
#include "../Include/constants.h"

std::string get_shaders(const char *shader_path) {
  std::string fragment_source = get_file_contents(shader_path);
  return fragment_source;
}