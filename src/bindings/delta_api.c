/**
 * @file delta_api.c
 * @brief Delta Robot Controller-compatible Lua API bindings for lu5.
 *
 * All functions in this file are safe stubs. When hardware is not available
 * (which is always the case in lu5), they:
 *   - Return sensible default values
 *   - Do not crash
 *   - Log a warning indicating "stubbed/not connected"
 *
 * DELAY is the only function that has real behaviour:
 *   - On native builds: performs a real sleep via nanosleep/usleep
 *   - On WASM builds:   safe no-op with a warning
 */

#include "delta_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lu5_logger.h"

/* -------------------------------------------------------------------------
 * Platform sleep support
 * ------------------------------------------------------------------------- */
#ifndef LU5_WASM
#  if defined(_WIN32) || defined(_WIN64)
     /* Windows (MinGW/MSYS2) */
#    include <windows.h>
     static void lu5_sleep_seconds(double seconds) {
         DWORD ms = (DWORD)(seconds * 1000.0);
         Sleep(ms);
     }
#  else
     /* POSIX (Linux, macOS) */
#    include <time.h>
     static void lu5_sleep_seconds(double seconds) {
         struct timespec ts;
         ts.tv_sec  = (time_t)seconds;
         ts.tv_nsec = (long)((seconds - (double)ts.tv_sec) * 1e9);
         nanosleep(&ts, NULL);
     }
#  endif
#endif /* LU5_WASM */

/* -------------------------------------------------------------------------
 * Warning helper macro
 * ------------------------------------------------------------------------- */
#define DELTA_STUB_WARN(fname) \
    LU5_WARN("[Delta API] %s: stubbed/not connected. Hardware not available.", fname)

/* =========================================================================
 * Socket userdata metatable name
 * ========================================================================= */
#define DELTA_SOCKET_MT "DeltaSocket"

/* -------------------------------------------------------------------------
 * Socket stub internal state (stored in userdata)
 * ------------------------------------------------------------------------- */
typedef struct {
    int  is_server; /**< 1 if server, 0 if client */
    int  port;      /**< port number */
} delta_socket_t;

/* -------------------------------------------------------------------------
 * Socket method: Send
 * ------------------------------------------------------------------------- */
static int delta_socket_Send(lua_State *L)
{
    DELTA_STUB_WARN("Socket:Send");
    /* Accept any cmd argument - do nothing */
    return 0;
}

/* -------------------------------------------------------------------------
 * Socket method: Receive
 * ------------------------------------------------------------------------- */
static int delta_socket_Receive(lua_State *L)
{
    DELTA_STUB_WARN("Socket:Receive");
    /* Return an empty table (array) as stub */
    lua_newtable(L);
    return 1;
}

/* -------------------------------------------------------------------------
 * Socket method: Close
 * ------------------------------------------------------------------------- */
static int delta_socket_Close(lua_State *L)
{
    DELTA_STUB_WARN("Socket:Close");
    return 0;
}

/* -------------------------------------------------------------------------
 * Socket method: CheckStatus
 * ------------------------------------------------------------------------- */
static int delta_socket_CheckStatus(lua_State *L)
{
    DELTA_STUB_WARN("Socket:CheckStatus");
    /* Returns: port(number), status(string), err(number) */
    lua_pushinteger(L, 0);
    lua_pushstring(L, "DisConnected");
    lua_pushinteger(L, DELTA_SOCKET_ERR_NONE);
    return 3;
}

/* -------------------------------------------------------------------------
 * Socket metatable __index
 * ------------------------------------------------------------------------- */
static int delta_socket_index(lua_State *L)
{
    /* Stack: userdata, key */
    const char *key = lua_tostring(L, 2);
    if (!key) {
        lua_pushnil(L);
        return 1;
    }
    if (strcmp(key, "Send") == 0) {
        lua_pushcfunction(L, delta_socket_Send);
    } else if (strcmp(key, "Receive") == 0) {
        lua_pushcfunction(L, delta_socket_Receive);
    } else if (strcmp(key, "Close") == 0) {
        lua_pushcfunction(L, delta_socket_Close);
    } else if (strcmp(key, "CheckStatus") == 0) {
        lua_pushcfunction(L, delta_socket_CheckStatus);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

/* -------------------------------------------------------------------------
 * Internal helper: push a new socket stub userdata onto the Lua stack
 * ------------------------------------------------------------------------- */
static void delta_push_socket(lua_State *L, int port, int is_server)
{
    delta_socket_t *sock = (delta_socket_t *)lua_newuserdata(L, sizeof(delta_socket_t));
    sock->port      = port;
    sock->is_server = is_server;

    /* Set metatable */
    if (luaL_newmetatable(L, DELTA_SOCKET_MT)) {
        /* First time: populate metatable */
        lua_pushcfunction(L, delta_socket_index);
        lua_setfield(L, -2, "__index");
    }
    lua_setmetatable(L, -2);
}

/* =========================================================================
 * Internal registry key for AuxTasksAdd function list
 * ========================================================================= */
#define DELTA_AUX_TASKS_KEY "DeltaAuxTasks"

/* =========================================================================
 * Digital I/O
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_DI(lua_State *L)
{
    DELTA_STUB_WARN("DI");
    /* Return "OFF" for single pin, 0 for multi-pin numeric reads */
    int argc = lua_gettop(L);
    if (argc >= 2) {
        /* Multi-pin: return numeric 0 */
        lua_pushinteger(L, 0);
    } else {
        /* Single pin: return "OFF" */
        lua_pushstring(L, "OFF");
    }
    return 1;
}

/* PUBLIC_INTERFACE */
int delta_DO(lua_State *L)
{
    DELTA_STUB_WARN("DO");
    /* No return value */
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_ExtDI(lua_State *L)
{
    DELTA_STUB_WARN("ExtDI");
    lua_pushstring(L, "OFF");
    return 1;
}

/* PUBLIC_INTERFACE */
int delta_ExtDO(lua_State *L)
{
    DELTA_STUB_WARN("ExtDO");
    return 0;
}

/* =========================================================================
 * Motion
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_MovP(lua_State *L)
{
    DELTA_STUB_WARN("MovP");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_MovL(lua_State *L)
{
    DELTA_STUB_WARN("MovL");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_MovJ(lua_State *L)
{
    DELTA_STUB_WARN("MovJ");
    return 0;
}

/* =========================================================================
 * Speed / Accel / Accuracy
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_SpdJ(lua_State *L)
{
    DELTA_STUB_WARN("SpdJ");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_AccJ(lua_State *L)
{
    DELTA_STUB_WARN("AccJ");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_DecJ(lua_State *L)
{
    DELTA_STUB_WARN("DecJ");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_SpdL(lua_State *L)
{
    DELTA_STUB_WARN("SpdL");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_AccL(lua_State *L)
{
    DELTA_STUB_WARN("AccL");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_DecL(lua_State *L)
{
    DELTA_STUB_WARN("DecL");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_Accur(lua_State *L)
{
    DELTA_STUB_WARN("Accur");
    return 0;
}

/* =========================================================================
 * Timing
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_DELAY(lua_State *L)
{
    double seconds = 0.0;
    if (lua_isnumber(L, 1)) {
        seconds = lua_tonumber(L, 1);
    } else {
        LU5_WARN("[Delta API] DELAY: expected a number argument (seconds).");
        return 0;
    }

    if (seconds < 0.001) {
        seconds = 0.001; /* clamp to minimum */
    }

#ifdef LU5_WASM
    /* WASM: cannot block, emit a warning and return immediately */
    LU5_WARN("[Delta API] DELAY(%.4f): sleep not supported on WASM, skipping.", seconds);
#else
    /* Native: perform a real sleep */
    lu5_sleep_seconds(seconds);
#endif

    return 0;
}

/* PUBLIC_INTERFACE */
int delta_WAIT(lua_State *L)
{
    DELTA_STUB_WARN("WAIT");
    /* Stub: return immediately without waiting */
    return 0;
}

/* =========================================================================
 * Points
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_SetGlobalPoint(lua_State *L)
{
    DELTA_STUB_WARN("SetGlobalPoint");
    return 0;
}

/* PUBLIC_INTERFACE */
int delta_ReadPoint(lua_State *L)
{
    DELTA_STUB_WARN("ReadPoint");
    /* Return 0.0 as the default value for any point item */
    lua_pushnumber(L, 0.0);
    return 1;
}

/* =========================================================================
 * Modbus
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_ReadModbus(lua_State *L)
{
    DELTA_STUB_WARN("ReadModbus");
    /* Return 0 as the stub register value */
    lua_pushinteger(L, 0);
    return 1;
}

/* PUBLIC_INTERFACE */
int delta_WriteModbus(lua_State *L)
{
    DELTA_STUB_WARN("WriteModbus");
    return 0;
}

/* =========================================================================
 * Sockets
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_SocketClass(lua_State *L)
{
    DELTA_STUB_WARN("SocketClass");
    int port = 0;
    if (lua_gettop(L) >= 2 && lua_isnumber(L, 2)) {
        port = (int)lua_tointeger(L, 2);
    }
    /* Push a stub socket client userdata */
    delta_push_socket(L, port, 0);
    return 1;
}

/* PUBLIC_INTERFACE */
int delta_SocketServer(lua_State *L)
{
    DELTA_STUB_WARN("SocketServer");
    int port = 0;
    if (lua_gettop(L) >= 1 && lua_isnumber(L, 1)) {
        port = (int)lua_tointeger(L, 1);
    }
    /* Push a stub socket server userdata */
    delta_push_socket(L, port, 1);
    return 1;
}

/* PUBLIC_INTERFACE */
int delta_CheckAllStatus(lua_State *L)
{
    DELTA_STUB_WARN("CheckAllStatus");
    /* Return three empty tables: ports[], statuses[], errors[] */
    lua_newtable(L);
    lua_newtable(L);
    lua_newtable(L);
    return 3;
}

/* PUBLIC_INTERFACE */
int delta_SocketVersion(lua_State *L)
{
    DELTA_STUB_WARN("SocketVersion");
    printf("[Delta API] SocketVersion: stubbed/not connected\n");
    fflush(stdout);
    return 0;
}

/* =========================================================================
 * Multi-task
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_AuxTasksAdd(lua_State *L)
{
    DELTA_STUB_WARN("AuxTasksAdd");

    int argc = lua_gettop(L);

    /* Store all function arguments in a Lua registry table */
    lua_newtable(L);                    /* new list table */
    for (int i = 1; i <= argc; i++) {
        if (lua_isfunction(L, i)) {
            lua_pushvalue(L, i);        /* push the function */
            lua_rawseti(L, -2, i);      /* list[i] = fn */
        } else {
            LU5_WARN("[Delta API] AuxTasksAdd: argument %d is not a function, skipping.", i);
        }
    }

    /* Store the list in the Lua registry */
    lua_setfield(L, LUA_REGISTRYINDEX, DELTA_AUX_TASKS_KEY);

    return 0;
}

/* PUBLIC_INTERFACE */
int delta_AuxTasks(lua_State *L)
{
    DELTA_STUB_WARN("AuxTasks");

    /* Retrieve the stored function list from the registry */
    lua_getfield(L, LUA_REGISTRYINDEX, DELTA_AUX_TASKS_KEY);
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        LU5_WARN("[Delta API] AuxTasks: no tasks registered. Call AuxTasksAdd first.");
        return 0;
    }

    /* Call each registered function once (cooperative round-robin stub) */
    int n = (int)lua_rawlen(L, -1);
    for (int i = 1; i <= n; i++) {
        lua_rawgeti(L, -1, i);          /* push function */
        if (lua_isfunction(L, -1)) {
            /* Call with 0 args, 0 results; on error print and continue */
            if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                const char *err = lua_tostring(L, -1);
                LU5_WARN("[Delta API] AuxTasks: error in task %d: %s", i, err ? err : "(unknown)");
                lua_pop(L, 1);          /* pop error */
            }
        } else {
            lua_pop(L, 1);             /* pop non-function */
        }
    }
    lua_pop(L, 1); /* pop the table */

    return 0;
}

/* =========================================================================
 * Utilities
 * ========================================================================= */

/* PUBLIC_INTERFACE */
int delta_split(lua_State *L)
{
    /* Validate arguments */
    if (lua_gettop(L) < 2) {
        lua_newtable(L);
        return 1;
    }

    const char *str = lua_tostring(L, 1);
    const char *sep = lua_tostring(L, 2);

    if (!str || !sep || sep[0] == '\0') {
        /* No separator or empty separator: return the whole string as one element */
        lua_newtable(L);
        if (str) {
            lua_pushstring(L, str);
            lua_rawseti(L, -2, 1);
        }
        return 1;
    }

    /* Result table */
    lua_newtable(L);

    int idx    = 1;          /* Lua table index (1-based) */
    size_t sep_len = strlen(sep);
    const char *cur  = str;
    const char *found;

    while ((found = strstr(cur, sep)) != NULL) {
        /* Push substring [cur, found) */
        lua_pushlstring(L, cur, (size_t)(found - cur));
        lua_rawseti(L, -2, idx++);
        cur = found + sep_len;
    }

    /* Push the last segment after the final separator */
    lua_pushstring(L, cur);
    lua_rawseti(L, -2, idx);

    return 1;
}

/* =========================================================================
 * Registration
 * ========================================================================= */

/* PUBLIC_INTERFACE */
void lu5_register_delta_api(lua_State *L)
{
    /* --- Digital I/O --- */
    lua_pushcfunction(L, delta_DI);    lua_setglobal(L, "DI");
    lua_pushcfunction(L, delta_DO);    lua_setglobal(L, "DO");
    lua_pushcfunction(L, delta_ExtDI); lua_setglobal(L, "ExtDI");
    lua_pushcfunction(L, delta_ExtDO); lua_setglobal(L, "ExtDO");

    /* --- Motion --- */
    lua_pushcfunction(L, delta_MovP);  lua_setglobal(L, "MovP");
    lua_pushcfunction(L, delta_MovL);  lua_setglobal(L, "MovL");
    lua_pushcfunction(L, delta_MovJ);  lua_setglobal(L, "MovJ");

    /* --- Speed / Accel / Accuracy --- */
    lua_pushcfunction(L, delta_SpdJ);  lua_setglobal(L, "SpdJ");
    lua_pushcfunction(L, delta_AccJ);  lua_setglobal(L, "AccJ");
    lua_pushcfunction(L, delta_DecJ);  lua_setglobal(L, "DecJ");
    lua_pushcfunction(L, delta_SpdL);  lua_setglobal(L, "SpdL");
    lua_pushcfunction(L, delta_AccL);  lua_setglobal(L, "AccL");
    lua_pushcfunction(L, delta_DecL);  lua_setglobal(L, "DecL");
    lua_pushcfunction(L, delta_Accur); lua_setglobal(L, "Accur");

    /* --- Timing --- */
    lua_pushcfunction(L, delta_DELAY); lua_setglobal(L, "DELAY");
    lua_pushcfunction(L, delta_WAIT);  lua_setglobal(L, "WAIT");

    /* --- Points --- */
    lua_pushcfunction(L, delta_SetGlobalPoint); lua_setglobal(L, "SetGlobalPoint");
    lua_pushcfunction(L, delta_ReadPoint);       lua_setglobal(L, "ReadPoint");

    /* --- Modbus --- */
    lua_pushcfunction(L, delta_ReadModbus);  lua_setglobal(L, "ReadModbus");
    lua_pushcfunction(L, delta_WriteModbus); lua_setglobal(L, "WriteModbus");

    /* --- Sockets --- */
    lua_pushcfunction(L, delta_SocketClass);    lua_setglobal(L, "SocketClass");
    lua_pushcfunction(L, delta_SocketServer);   lua_setglobal(L, "SocketServer");
    lua_pushcfunction(L, delta_CheckAllStatus); lua_setglobal(L, "CheckAllStatus");
    lua_pushcfunction(L, delta_SocketVersion);  lua_setglobal(L, "SocketVersion");

    /* --- Multi-task --- */
    lua_pushcfunction(L, delta_AuxTasksAdd); lua_setglobal(L, "AuxTasksAdd");
    lua_pushcfunction(L, delta_AuxTasks);    lua_setglobal(L, "AuxTasks");

    /* --- Utilities --- */
    lua_pushcfunction(L, delta_split); lua_setglobal(L, "split");

    /* --- Socket error constants --- */
    lua_pushinteger(L, DELTA_SOCKET_ERR_NONE);              lua_setglobal(L, "SOCKET_ERR_NONE");
    lua_pushinteger(L, DELTA_SOCKET_ERR_SESSION_INVALID);   lua_setglobal(L, "SOCKET_ERR_SESSION_INVALID");
    lua_pushinteger(L, DELTA_SOCKET_ERR_BUSY);              lua_setglobal(L, "SOCKET_ERR_BUSY");
    lua_pushinteger(L, DELTA_SOCKET_ERR_SEND_FAIL);         lua_setglobal(L, "SOCKET_ERR_SEND_FAIL");
    lua_pushinteger(L, DELTA_SOCKET_ERR_SENT_WITH_SBYTE);   lua_setglobal(L, "SOCKET_ERR_SENT_WITH_SBYTE");
    lua_pushinteger(L, DELTA_SOCKET_ERR_PACKET_TOO_SHORT);  lua_setglobal(L, "SOCKET_ERR_PACKET_TOO_SHORT");
    lua_pushinteger(L, DELTA_SOCKET_ERR_ROLE_INCORRECT);    lua_setglobal(L, "SOCKET_ERR_ROLE_INCORRECT");
    lua_pushinteger(L, DELTA_SOCKET_ERR_CONN_FULL);         lua_setglobal(L, "SOCKET_ERR_CONN_FULL");
    lua_pushinteger(L, DELTA_SOCKET_ERR_CHANNEL_ERROR);     lua_setglobal(L, "SOCKET_ERR_CHANNEL_ERROR");
    lua_pushinteger(L, DELTA_SOCKET_ERR_IP_PORT_ZERO);      lua_setglobal(L, "SOCKET_ERR_IP_PORT_ZERO");
    lua_pushinteger(L, DELTA_SOCKET_ERR_PORT_OUT_OF_RANGE); lua_setglobal(L, "SOCKET_ERR_PORT_OUT_OF_RANGE");
    lua_pushinteger(L, DELTA_SOCKET_ERR_SOCKET_CREATE);     lua_setglobal(L, "SOCKET_ERR_SOCKET_CREATE");
    lua_pushinteger(L, DELTA_SOCKET_ERR_BIND_FAIL);         lua_setglobal(L, "SOCKET_ERR_BIND_FAIL");
    lua_pushinteger(L, DELTA_SOCKET_ERR_SETSOCKOPT);        lua_setglobal(L, "SOCKET_ERR_SETSOCKOPT");
    lua_pushinteger(L, DELTA_SOCKET_ERR_BIND);              lua_setglobal(L, "SOCKET_ERR_BIND");
    lua_pushinteger(L, DELTA_SOCKET_ERR_LISTEN);            lua_setglobal(L, "SOCKET_ERR_LISTEN");
    lua_pushinteger(L, DELTA_SOCKET_ERR_CONN_REFUSED);      lua_setglobal(L, "SOCKET_ERR_CONN_REFUSED");
    lua_pushinteger(L, DELTA_SOCKET_ERR_NO_END_CODE);       lua_setglobal(L, "SOCKET_ERR_NO_END_CODE");
}
