#include "perr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *program_invocation_short_name;

void perr_init(int argc, char *argv[])
{
  if(argc)
  {
    if((program_invocation_short_name = strrchr(argv[0], PATHDELIM)))
      program_invocation_short_name += 1;
    else
      program_invocation_short_name = argv[0];
  }
}

void vwarnx(const char *fmt, va_list args)
{
  fprintf(stderr, "%s: ", program_invocation_short_name);
  if(fmt)
    vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
}

void vwarn(const char *fmt, va_list args)
{
  int eno = errno;

  fprintf(stderr, "%s: ", program_invocation_short_name);
  if(fmt)
    vfprintf(stderr, fmt, args);
  fprintf(stderr, "%s%s\n", fmt ? ": " : "", strerror(eno));
}

void verrx(int eval, const char *fmt, va_list args)
{
  vwarnx(fmt, args);
  exit(eval);
}

void verr(int eval, const char *fmt, va_list args)
{
  vwarn(fmt, args);
  exit(eval);
}

void warnx(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vwarnx(fmt, args);
  va_end(args);
}

void errx(int eval, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  verrx(eval, fmt, args);
  va_end(args);
}

void warn(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vwarn(fmt, args);
  va_end(args);
}

void err(int eval, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  verr(eval, fmt, args);
  va_end(args);
}
