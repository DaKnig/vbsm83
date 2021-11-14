#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "exception.hpp"

bool enable_info = false;
unsigned error_count = 0;

bool info() {
    if (enable_info)
        fputs("\033[1m\033[93minfo: \033[0m", stdout);
    return enable_info;
}

/* Print a warning message to stderr.
 * Warnings should warn the iser of strange or unsafe behavior that does not
 * prevent compilation.
 */
void info(char const* fmt, ...) {
    if (!enable_info)
        return;
    va_list ap;

    fputs("\033[1m\033[93minfo: \033[0m", stdout);
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    putc('\n', stdout);
}

/* Print a warning message to stderr.
 * Warnings should warn the iser of strange or unsafe behavior that does not
 * prevent compilation.
 */
void warn(char const* fmt, ...) {
    va_list ap;

    fputs("\033[1m\033[95mwarn: \033[0m", stderr);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n', stderr);
}

/* Print an error message to stderr
 * This is for exceptions which should halt the program execution but are not
 * immediately fatal. This allows the program to continue running to find and
 * alert the user to other errors.
 */
void error(char const* fmt, ...) {
    va_list ap;

    fputs("\033[1m\033[31merror: \033[0m", stderr);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n', stderr);

    error_count++;
}

/* Print a fatal error message to stderr and exit.
 */
void fatal(char const* fmt, ...) {
    va_list ap;

    fputs("\033[1m\033[31mfatal: \033[0m", stderr);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    putc('\n', stderr);

    exit(1);
}