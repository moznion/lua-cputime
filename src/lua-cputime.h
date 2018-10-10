#ifndef LUACPUTIME_LUA_CPUTIME_H_
#define LUACPUTIME_LUA_CPUTIME_H_


#ifdef __cplusplus
extern "C" {
#endif

#define _GNU_SOURCE

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef WIN32

#include <windows.h>

#else

#include <sys/time.h>
#include <sys/resource.h>

#endif

#ifdef __cplusplus
}
#endif

#define CPUTIME_VERSION "0.1.0-0"
#define CPUTIME_LIBNAME "cputime"
#define CPUTIME_COPYRIGHT "Copyright © 2018 moznion, http://moznion.net/ <moznion@gmail.com>"
#define CPUTIME_DESCRIPTION "A bridge library of CPU time measurement"

#endif

