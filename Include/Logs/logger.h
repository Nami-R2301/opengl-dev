//
// Created by nami on 5/16/22.
//

#ifndef OPENGL_DEV_LOGGER_H
#define OPENGL_DEV_LOGGER_H

#include "../Game logic/time.h"
#include <cstdlib>
#include <cstring>

#define INFO 1
#define ERROR 2
#define ERROR_OPENING_FILE 3
#define ERROR_SNPRINTF -13

class Logger
{
public:
  static void open_file();
  static void alert(const char *info, int info_type = INFO, bool inline_ = false);
  static void close_file();
private:
  static void save_to_file(const char *info);
};

#endif //OPENGL_DEV_LOGGER_H
