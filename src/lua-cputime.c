#include "lua-cputime.h"

#ifdef WIN32
static int get_process_cputime(lua_State* L) {
    FILETIME created, exited, stime, utime;

    const BOOL succ = GetProcessTimes(GetCurrentProcess(), &created, &exited, &stime, &utime);
    if (succ) {
        lua_pushnumber(L, ((uint64_t) utime.dwHighDateTime << 32 | utime.dwLowDateTime) / 10);
        lua_pushnumber(L, ((uint64_t) stime.dwHighDateTime << 32 | stime.dwLowDateTime) / 10);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushstring(L, "failed to measure the CPU time");
    }

    return 3;
}
#else
typedef struct _cputime_result {
    unsigned long utime;
    unsigned long stime;
    char* error;
} _cputime_result_t;

static _cputime_result_t _get_cputime(int who) {
    struct rusage usage;

    if (getrusage(who, &usage) < 0) {
        const _cputime_result_t result = {0, 0, "failed to measure the CPU time"};
        return result;
    }

    const struct timeval utime = usage.ru_utime;
    const struct timeval stime = usage.ru_stime;

    const _cputime_result_t result = {
        utime.tv_sec * 1000000 + utime.tv_usec,
        stime.tv_sec * 1000000 + stime.tv_usec,
        NULL
    };
    return result;
}

static int get_process_cputime(lua_State* L) {
    const _cputime_result_t result = _get_cputime(RUSAGE_SELF);

    if (result.error == NULL) {
        lua_pushnumber(L, result.utime);
        lua_pushnumber(L, result.stime);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushstring(L, result.error);
    }

    return 3;
}
#endif

#if defined(__linux__) || defined(WIN32)
static int get_thread_cputime(lua_State* L) {
#ifdef __linux__
    const _cputime_result_t result = _get_cputime(RUSAGE_THREAD);

    if (result.error == NULL) {
        lua_pushnumber(L, result.utime);
        lua_pushnumber(L, result.stime);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushstring(L, result.error);
    }
#elif WIN32
    FILETIME created, exited, stime, utime;

    const BOOL succ = GetThreadTimes(GetCurrentThread(), &created, &exited, &stime, &utime);
    if (succ) {
        lua_pushnumber(L, ((uint64_t) utime.dwHighDateTime << 32 | utime.dwLowDateTime) / 10);
        lua_pushnumber(L, ((uint64_t) stime.dwHighDateTime << 32 | stime.dwLowDateTime) / 10);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushstring(L, "failed to measure the CPU time");
    }
#endif
    return 3;
}
#endif

static const struct luaL_Reg R[] = {
    {"get_process_cputime", get_process_cputime},
#if defined(__linux__) || defined(WIN32)
    {"get_thread_cputime", get_thread_cputime},
#endif
    {NULL, NULL},
};

#ifdef __cplusplus
extern "C" {
#endif

LUALIB_API int luaopen_cputime(lua_State * L) {
    /*
     * Register module
     */
#if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM < 502 // lua < 5.2
    luaL_register(L, CPUTIME_LIBNAME, R);
#else
    lua_newtable(L);
    luaL_setfuncs(L, R, 0);
#endif

    /*
     * Register module information
     */
    lua_pushliteral(L, CPUTIME_VERSION);
    lua_setfield(L, -2, "_VERSION");

    lua_pushliteral(L, CPUTIME_COPYRIGHT);
    lua_setfield(L, -2, "_COPYRIGHT");

    lua_pushliteral(L, CPUTIME_DESCRIPTION);
    lua_setfield(L, -2, "_DESCRIPTION");

    return 1;
}

#ifdef __cplusplus
}
#endif

