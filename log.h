#ifndef LOG_H
#define LOG_H

/******************************************************
 * Includes
 ******************************************************/
#include <stdio.h>
#include <stdbool.h>

/******************************************************
 * Function Headers
 ******************************************************/
void log_msg(const char *msg);
void flog_msg(const char *format, ...);
void log_init();
void log_end(bool print_log);

#endif // LOG_H