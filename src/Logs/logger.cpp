//
// Created by nami on 5/16/22.
//

#include "../../Include/Logs/logger.h"

static FILE *file_ptr = nullptr;

void Logger::open_file()
{
  file_ptr = fopen("../src/Logs/log.txt", "a");
  if (file_ptr == nullptr)
  {
    fprintf(stderr, "ERROR OPENING FILE! NO SUCH PARENT DIRECTORY!\n");
    exit(ERROR_OPENING_FILE);
  }
}

void Logger::save_to_file(const char *info)
{
  if (file_ptr != nullptr)
  {
    fprintf(file_ptr, "%s", info);
  }
}

void Logger::alert(const char *info, int info_type, bool inline_)
{
  auto time = Game_time::get_real_time();  // Get std::time_t struct.
  char *current_time = ctime(&time);  // Transform to const char*.
  current_time[strlen(current_time) - 1] = '\0';  // Remove newline.

  char type[6];
  if (info_type == INFO) snprintf(type, 5, "INFO");
  else if (info_type == ERROR) snprintf(type, 6, "ERROR");

  char buffer[256];
  if (snprintf(buffer, 256, "[%s] [%s] : %s", type, current_time, info) < 0)
  {
    fprintf(stderr, "ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n");
    exit(ERROR_SNPRINTF);
  }
  if (!inline_)
  {
    fprintf(stdout, "%s", buffer);
    save_to_file(buffer);
  } else
  {
    fprintf(stdout, "%s", info);
    save_to_file(info);
  }
}

void Logger::close_file()
{
  fclose(file_ptr);
}
