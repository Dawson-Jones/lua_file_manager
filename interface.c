#include <stdio.h>
#include <lauxlib.h>
#include <lua.h>

#include "./file_remove.h"

#define DEBUG 1
#if DEBUG

int clean_ex_file(lua_State *l);

static const luaL_Reg file_manage[] = {
    {"clean_ex_file", clean_ex_file},
    {NULL, NULL}
};


int clean_ex_file(lua_State *l) {
    luaL_checktype(l, -3, LUA_TSTRING);
    luaL_checktype(l, -2, LUA_TNUMBER);
    luaL_checktype(l, -1, LUA_TNUMBER);

    const char *path = lua_tostring(l, -3);
    time_t expire = lua_tonumber(l, -2);
    int mode = lua_tonumber(l, -1);

    remove_expired_file(path, expire, mode);

    return 1;
}

int luaopen_filemanager(lua_State *L) {
    luaL_register(L, "filemanager", file_manage);
    return 1;
}

#else

int main() {
    char str[1000];
    int time;
    printf("type the dir name:\n");
    scanf("%s", str);
    printf("expire time:\n");
    scanf("%d", &time);
    remove_expired_file(str, time, 1);
    printf("remove_file: %d, remove_dir: %d, rest: %d\n", remove_file, remove_dir, rest);
}

#endif