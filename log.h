#ifndef LOG_H
#define LOG_H


/******************************************************
 * Includes
 ******************************************************/
#include <stdio.h>


/******************************************************
 * Function Headers
 ******************************************************/
void log_msg(const char *msg);
void flog_msg(const char *format, ...);
void log_init();

#endif // LOG_H