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
static const char *src = NULL;

//1 - lua 管理器 注冊 c 接口
//2 - lua 应用 注册
//3 - 当注册时间发生时 c 调用 lua管理器 并传入标识符
//4 - lua 管理器 通过 c 接口 通讯 lua

static int setnotify(lua_State *L)
{
    src = luaL_checkstring(L, 1);    //出栈获取源字符串
    lua_callback = luaL_ref(L,LUA_REGISTRYINDEX);//LUA_REGISTRYINDEX);
    return 0;
}

static int testnotify(lua_State *L)
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, lua_callback); //压栈
    lua_pushstring(L, "how");
    lua_call(L, 1, 0);//访问栈
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

LUALIB_API int luaopen_haha( lua_State *L )
{
    //luaL_newmetarotable(L,"test.chan", (void *)cblib);
    return 0;
}

//DRIVER_REGISTER(HAHA, haha, NULL, NULL, NULL);
MODULE_REGISTER_MAPPED(HAHA, haha, cblib, luaopen_haha);

#endif

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

// 这其中最关键的是调用函数的使用，在C中调用Lua函数的API主要由以下几个：

// （1）void lua_call (lua_State *L, int nargs, int nresults);
// 　　函数调用，nargs表示参数的个数，nresults表示返回值的个数
// 　　首先将lua函数压栈，然后将参数依次压栈，最后调用函数即可
// 　　函数调用时，参数和函数都会pop出栈，调用返回后，结果会push进栈
// 　　nresults==LUA_MULTRET，所有的返回值都会push进栈
// 　　nresults!=LUA_MULTRET，返回值个数根据nresults来调整
// 　　Lua语句：

// a = f("how", t.x, 14)
// 　　在C中的实现：

// 复制代码
// lua_getglobal(L, "f"); 　　　　　　 // 函数入栈
// lua_pushstring(L, "how"); 　　　  // 参数1入栈
// lua_getglobal(L, "t");　　　　　　 // 表t入栈
// lua_getfield(L, -1, "x"); 　　　　  // 参数2入栈
// lua_remove(L, -2); 　　　　　　  // 跳t出栈
// lua_pushinteger(L, 14);　　　　 // 参数3入栈
// lua_call(L, 3, 1); 　　　　　　     // 调用函数，参数和函数都会出栈
// lua_setglobal(L, "a");　　　　     // 给a赋值，栈顶出栈
// 复制代码
// 　　上述代码执行完毕后，堆栈状态恢复原样。

// （2）int lua_pcall (lua_State *L, int nargs, int nresults, int msgh);
// 　　函数调用，在安全模式下，并且可以添加错误处理函数。
// 　　如果调用期间发生error，lua_pcall会捕获之，然后push stack一个错误信息(会先将函数和参数pop出栈)，并且返回一个error code（非0的一个值）。
// 　　发生error时，如果指定了错误处理函数，会在error message入栈前调用错误处理函数，具体由msgh参数来决定：
// 　　（1）msgh==0，不指定错误处理函数，入栈信息不变；
// 　　（2）msgh!=0，msgh表示错误处理函数的堆栈index，错误处理函数会以error message为参数，并将返回的新的error message入栈。主要用来给error message添加　　更多的debug信息，比如堆栈跟踪，因为这些信息在pcall调用完之后是收集不到的。
// 　　函数返回代码：
// 　　LUA_OK(0)：调用成功
// 　　LUA_ERRRUN：runtime error
// 　　LUA_ERRMEM：内存分配错误，这种情况下不会调用错误处理函数
// 　　LUA_ERRERR：调用错误处理函数时出错，当然，不会再进一步调用错误处理函数
// 　　LUA_ERRGCMM：调用metamethod.__gc时报错，由gc引起，和函数本身没关系

// （3）int lua_pcallk (lua_State *L, int nargs, int nresults, int errfunc, int ctx, lua_CFunction k);
// 　　函数调用，在安全模式下，并且允许函数yield。