//
// Created by nami on 5/16/22.
//

#ifndef OPENGL_DEV_LOGGER_H
#define OPENGL_DEV_LOGGER_H

// Game_time
#include "../Game logic/game_time.h"

// strlen, std::string and snprintf.
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdarg>

#define INFO 1
#define ERROR 2
#define ERROR_OPENING_FILE 3
#define ERROR_HEAP_ALLOC -11
#define ERROR_SNPRINTF -13

class Logger
{
public:
  static void open_file();
  static void alert(int info_type = INFO, const char *format = "\n", ...);
  static void close_file();
private:
  static void save_to_file(const char *info);
};

#endif //OPENGL_DEV_LOGGER_H
