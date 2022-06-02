//
// Created by nami on 5/16/22.
//

#include "logger.h"

static FILE *file_ptr = nullptr;

void open_file()
{
  file_ptr = fopen("../src/Logs/log.txt", "a");
  if (file_ptr == nullptr)
  {
    fprintf(stderr, "ERROR OPENING FILE! NO SUCH PARENT DIRECTORY!\n");
    exit(ERROR_OPENING_FILE);
  }
}

void save_to_file(const char *info)
{
  if (file_ptr != nullptr)
  {
    fprintf(file_ptr, "%s\n", info);
  }
}

void alert(int info_type, const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char *string;
  vasprintf(&string, format, args);

  char type[6];
  if (info_type == INFO) snprintf(type, 5, "INFO");
  else if (info_type == ERROR) snprintf(type, 6, "ERROR");

  auto time = Game_time::get_real_time();  // Get std::time_t struct.
  char *current_time = ctime(&time);  // Transform to const char*.
  current_time[strlen(current_time) - 1] = '\0';  // Remove newline.

  unsigned int buffer_size = strlen(string) + strlen(current_time) + strlen(type) + 9;  // 9 extra format chars.
  char buffer[buffer_size];
  if (snprintf(buffer, buffer_size, "[%s] [%s] : %s", type, current_time, string) < 0)
  {
    fprintf(stderr, "ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n");
    exit(ERROR_SNPRINTF);
  }
  fprintf(stdout, "%s\n", buffer);
  save_to_file(buffer);
  free(string);
  va_end(args);
}

void close_file()
{
  fclose(file_ptr);
}
