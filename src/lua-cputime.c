#include "lua-cputime.h"

typedef struct _cputime_result {
    struct tms* tms;
    char* error;
} _cputime_result_t;

static _cputime_result_t _get_cputime() {
    struct tms t;
    const clock_t clocktime = times(&t);
    if (clocktime < 0) {
        const _cputime_result_t result = {NULL, "failed to measure the CPU time"};
        return result;
    }

    const _cputime_result_t result = {&t, NULL};
    return result;
}

static int get_cputime(lua_State* L) {
    const _cputime_result_t result = _get_cputime();

    if (result.error == NULL) {
        lua_pushnumber(L, (double)result.tms->tms_utime / sysconf(_SC_CLK_TCK) / 1000);
        lua_pushnumber(L, (double)result.tms->tms_stime / sysconf(_SC_CLK_TCK) / 1000);
        lua_pushnumber(L, (double)result.tms->tms_cutime / sysconf(_SC_CLK_TCK) / 1000);
        lua_pushnumber(L, (double)result.tms->tms_cstime / sysconf(_SC_CLK_TCK) / 1000);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushstring(L, result.error);
    }

    return 5;
}

static const struct luaL_Reg R[] = {
    {"get_cputime", get_cputime},
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

