// Module for interfacing with PIO

#include "luartos.h"

#if CONFIG_LUA_RTOS_LUA_USE_HAHA

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "error.h"
#include "lualib.h"
#include "lauxlib.h"
#include "auxmods.h"
#include "modules.h"
#include "lhb_test.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <sys/status.h>

#include <drivers/cpu.h>
#include <drivers/gpio.h>

#include "esp_intr.h"

static int lua_callback = LUA_REFNIL;

static int setnotify(lua_State *L)
{
    lua_callback = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

static int testnotify(lua_State *L)
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, lua_callback); //压栈
    lua_call(L, 0, 0);//访问栈
    return 0;
}

static int testenv(lua_State *L)
{
    lua_getglobal(L, "defcallback");
    lua_call(L, 0, 0);
    return 0;
}

const int haha_errors;
const int haha_error_map;

static const LUA_REG_TYPE cblib[] =
{
    { LSTRKEY("setnotify"     ),          LFUNCVAL( setnotify          ) }, //测试 使用
    { LSTRKEY("testnotify"    ),          LFUNCVAL( testnotify         ) },
    { LSTRKEY("testenv"       ),          LFUNCVAL( testenv            ) },
    // DRIVER_REGISTER_LUA_ERRORS(haha)
    { LNILKEY, LNILVAL }
};

// int luaopen_cb(lua_State *L)
// {
//   luaL_register(L, "cb", cblib);
//   return 1;
// }


// static const LUA_REG_TYPE ltest_map[] = {
//     { LNILKEY, LNILVAL }
// };

// static const LUA_REG_TYPE ltest_channel_map[] = {
//   { LNILKEY, LNILVAL }

// };

LUALIB_API int luaopen_haha( lua_State *L )
{
    printf("linghaibin test\n");
    //luaL_newmetarotable(L,"test.chan", (void *)cblib);
    return 0;
}

//DRIVER_REGISTER(HAHA, haha, NULL, NULL, NULL);
MODULE_REGISTER_MAPPED(HAHA, haha, cblib, luaopen_haha);

#endif


// #include <stdio.h>
// #include <stdlib.h>
// #include "lua.h"
// #include "lualib.h"
// #include "lauxlib.h"

// static int lua_callback = LUA_REFNIL;

// static int setnotify(lua_State *L)
// {
//   lua_callback = luaL_ref(L, LUA_REGISTRYINDEX);
//   return 0;
// }

// static int testnotify(lua_State *L)
// {
//   lua_rawgeti(L, LUA_REGISTRYINDEX, lua_callback);
//   lua_call(L, 0, 0);
// }

// static int testenv(lua_State *L)
// {
//   lua_getglobal(L, "defcallback");
//   lua_call(L, 0, 0);
// }

// static const luaL_Reg cblib[] = {
//   {"setnotify", setnotify},
//   {"testnotify", testnotify},
//   {"testenv", testenv},
//   {NULL, NULL}
// };

// int luaopen_cb(lua_State *L)
// {
//   luaL_register(L, "cb", cblib);
//   return 1;
// }

// require("cb")

// function callback(  )
//   print "Callback"
// end

// function defcallback()
//   print "Predef callback"
// end

// cb.setnotify(callback)
// cb.testnotify()
// print "Done"
// cb.testenv()
