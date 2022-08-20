#ifndef HDR_PERR
#define HDR_PERR

#include <stdarg.h>

#undef  program_invocation_short_name
#undef  vwarnx
#undef  vwarn
#undef  verrx
#undef  verr
#undef  warnx
#undef  warn
#undef  errx
#undef  err

#define program_invocation_short_name portable_program_invocation_short_name
#define vwarnx                        portable_vwarnx
#define vwarn                         portable_vwarn
#define verrx                         portable_verrx
#define verr                          portable_verr
#define warnx                         portable_warnx
#define warn                          portable_warn
#define errx                          portable_errx
#define err                           portable_err

#ifdef _WIN32
#define PATHDELIM '\\'
#else  /* _WIN32 */
#define PATHDELIM '/'
#endif  /* _WIN32 */

extern char *program_invocation_short_name;

#undef noreturn
#ifdef __cplusplus
#define noreturn [[noreturn]]
extern "C" {
#else  /* __cplusplus */
#define noreturn _Noreturn
#endif  /* __cplusplus */

void perr_init(int argc, char *argv[]);
void vwarnx(const char *fmt, va_list args);
noreturn void verrx(int eval, const char *fmt, va_list args);
void vwarn(const char *fmt, va_list args);
noreturn void verr(int eval, const char *fmt, va_list args);
void warnx(const char *fmt, ...);
noreturn void errx(int eval, const char *fmt, ...);
void warn(const char *fmt, ...);
noreturn void err(int eval, const char *fmt, ...);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* HDR_PERR */
