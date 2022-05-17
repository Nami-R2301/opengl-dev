//
// Created by nami on 5/16/22.
//

#include "../../Include/Logs/logger.h"

[[maybe_unused]] void save_to_file(const char *info)
{
  const char *current_time = Time::get_real_time();
  FILE *file_ptr = fopen("log.txt", "a");
  if (file_ptr == nullptr)
  {
    printf("Error!");
    exit(1);
  }
  fprintf(file_ptr, "[%s] : %s", current_time, info);
}

void output_on_screen(const char *info, int info_type, bool inline_)
{
  const char *current_time = Time::get_real_time();
  char buffer[20];
  snprintf(buffer, 20, "%s", current_time);
  char type[6];
  if (info_type == INFO) snprintf(type, 5, "INFO");
  else if (info_type == ERROR) snprintf(type, 6, "ERROR");
  if (!inline_) printf("[%s] [%s] : %s", type, buffer, info);
  else printf("%s", info);
}
