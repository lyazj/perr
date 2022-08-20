#include "perr.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

static void run_warnx(void);
static void run_warn(void);
static void run_errx(void);
static void run_err(void);

int main(void)
{
  pid_t pid;
  void (*func[4])(void) = {
    run_warnx,
    run_warn,
    run_errx,
    run_err,
  };
  int i, wstatus;

  for(i = 0; i < 4; ++i)
  {
    pid = fork();
    if(pid < 0)
    {
      perror(__func__);
      exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
      errno = 0;
      func[i]();
      exit(EXIT_SUCCESS);
    }
    pid = waitpid(pid, &wstatus, 0);
    if(pid < 0)
    {
      perror(__func__);
      exit(EXIT_FAILURE);
    }
    if(!WIFEXITED(wstatus))
      fprintf(stderr, "process %d"
          " terminated abnormally\n", pid);
    else
      fprintf(stderr, "process %d"
          " exited with status code %d\n", pid, WEXITSTATUS(wstatus));
  }

  return 0;
}

void run_warnx(void)
{
  program_invocation_short_name = (char *)__func__;
  warnx("%d", getpid());
}

void run_warn(void)
{
  program_invocation_short_name = (char *)__func__;
  warn("%d", getpid());
}

void run_errx(void)
{
  program_invocation_short_name = (char *)__func__;
  errx(EXIT_FAILURE, "%d", getpid());
}

void run_err(void)
{
  program_invocation_short_name = (char *)__func__;
  err(EXIT_FAILURE, "%d", getpid());
}
