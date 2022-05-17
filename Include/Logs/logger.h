//
// Created by nami on 5/16/22.
//

#ifndef OPENGL_DEV_LOGGER_H
#define OPENGL_DEV_LOGGER_H

#include "../Game logic/time.h"
#include <cstdlib>
#include <cstdio>

#define INFO 1
#define ERROR 2

[[maybe_unused]] void save_to_file(const char *info);
void output_on_screen(const char *info, int info_type = INFO, bool inline_ = false);

#endif //OPENGL_DEV_LOGGER_H
