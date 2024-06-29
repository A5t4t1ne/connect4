/******************************************************
 * File: log.c
 *
 * Author: David Jäggli
 *
 * Description: A simple logging utility.
 ******************************************************/

/******************************************************
 * Includes
 * ***************************************************/
#include "log.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/******************************************************
 * Function Definitions
 ******************************************************/
void log_msg(const char *msg)
{
    printf("%s\n", msg);
}

void flog_msg(const char *format, ...)
{
    FILE *f = fopen("log.txt", "a");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Create a new format string that appends a newline character
    char *log_line = malloc(strlen(format) + 2); // +2 for '\n' and '\0'
    if (log_line == NULL)
    {
        perror("Malloc failed");
        fclose(f);
        return;
    }
    sprintf(log_line, "%s", format);

    va_list args;
    va_start(args, format);
    vfprintf(f, log_line, args);
    va_end(args);

    free(log_line); // Free the allocated memory
    fclose(f);
}

void log_init()
{
    FILE *f = fopen("log.txt", "w");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }

    fclose(f);
}