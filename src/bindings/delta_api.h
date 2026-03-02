#ifndef __LU5_DELTA_API_BINDINGS__
#define __LU5_DELTA_API_BINDINGS__

/**
 * @file delta_api.h
 * @brief Delta Robot Controller-compatible Lua API bindings for lu5.
 *
 * These are safe stubs that mirror the Delta robot controller API.
 * When hardware/PLC is not available, functions return sensible defaults
 * and log a warning indicating "stubbed/not connected".
 *
 * Grouped by:
 *   - Digital I/O:   DI, DO, ExtDI, ExtDO
 *   - Motion:        MovP, MovL, MovJ
 *   - Speed/Accel:   SpdJ, AccJ, DecJ, SpdL, AccL, DecL, Accur
 *   - Timing:        DELAY, WAIT
 *   - Points:        SetGlobalPoint, ReadPoint
 *   - Modbus:        ReadModbus, WriteModbus
 *   - Sockets:       SocketClass, SocketServer, CheckAllStatus, SocketVersion
 *   - Multi-task:    AuxTasksAdd, AuxTasks
 *   - Utilities:     split
 */

#include <lua.h>

/* =========================================================================
 * Digital I/O
 * ========================================================================= */

/**
 * DI - Read digital input pin status.
 *
 * Syntax (stub):
 *   status = DI(pin_index)
 *   status_num = DI(pin_index, length)
 *
 * @param pin_index  Pin number (1-24) or name string.
 * @param length     (optional) Number of pins to read continuously (1-24).
 * @return           ON/OFF status string, or numeric status for multi-pin reads.
 *
 * Stub behaviour: always returns "OFF" (0) and logs a warning.
 */
/* PUBLIC_INTERFACE */
int delta_DI(lua_State *L);

/**
 * DO - Set digital output pin state.
 *
 * Syntax (stub):
 *   DO(pin_index, status)
 *   DO(pin_index, status, delay_time)
 *   DO(pin_index, length, status_num)
 *   DO(pin_index, length, status_num, delay_time)
 *
 * @param pin_index  Pin number (1-12) or name string.
 * @param status     "ON" or "OFF".
 * @param delay_time (optional) Delay in seconds.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_DO(lua_State *L);

/**
 * ExtDI - Read external board digital input pin status.
 *
 * Syntax (stub):
 *   status = ExtDI(address_index, pin_index)
 *
 * @param address_index  Station number of the external board.
 * @param pin_index      Pin number on the external board.
 * @return               "OFF" always in stub mode.
 *
 * Stub behaviour: logs a warning, returns "OFF".
 */
/* PUBLIC_INTERFACE */
int delta_ExtDI(lua_State *L);

/**
 * ExtDO - Set external board digital output pin state.
 *
 * Syntax (stub):
 *   ExtDO(address_index, pin_index, status)
 *   ExtDO(address_index, pin_index, status, delay_time)
 *
 * @param address_index  Station number of the external board.
 * @param pin_index      Pin number on the external board.
 * @param status         "ON" or "OFF".
 * @param delay_time     (optional) Delay in seconds.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_ExtDO(lua_State *L);

/* =========================================================================
 * Motion
 * ========================================================================= */

/**
 * MovP - Move robot to a point using point-to-point motion.
 *
 * Syntax (stub):
 *   MovP(point)
 *   MovP(point + Offset(), Function() + ...)
 *
 * @param point  Target point name (string) or point number.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_MovP(lua_State *L);

/**
 * MovL - Move robot to a point using linear motion.
 *
 * Syntax (stub):
 *   MovL(point)
 *   MovL(point + Offset(), Function() + ...)
 *
 * @param point  Target point name (string) or point number.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_MovL(lua_State *L);

/**
 * MovJ - Move a single robot axis to a target angle.
 *
 * Syntax (stub):
 *   MovJ(joint, degree)
 *   MovJ(joint, degree, Function() + ...)
 *
 * @param joint   Axis number (1-6).
 * @param degree  Target angle in degrees (-360 to 360).
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_MovJ(lua_State *L);

/* =========================================================================
 * Speed / Accel / Accuracy
 * ========================================================================= */

/**
 * SpdJ - Set maximum joint speed (%).
 *
 * Syntax (stub):
 *   SpdJ(speed)
 *
 * @param speed  Speed percentage (0.001-100). Default: 10%.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_SpdJ(lua_State *L);

/**
 * AccJ - Set joint acceleration (%).
 *
 * Syntax (stub):
 *   AccJ(acceleration)
 *
 * @param acceleration  Acceleration percentage (0.001-100). Default: 10%.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_AccJ(lua_State *L);

/**
 * DecJ - Set joint deceleration (%).
 *
 * Syntax (stub):
 *   DecJ(deceleration)
 *
 * @param deceleration  Deceleration percentage (0.001-100). Default: 10%.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_DecJ(lua_State *L);

/**
 * SpdL - Set maximum linear speed (mm/sec).
 *
 * Syntax (stub):
 *   SpdL(speed)
 *
 * @param speed  Speed in mm/sec (1-2000). Default: 100 mm/sec.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_SpdL(lua_State *L);

/**
 * AccL - Set linear acceleration (mm/sec^2).
 *
 * Syntax (stub):
 *   AccL(acceleration)
 *
 * @param acceleration  Acceleration in mm/sec^2 (1-25000). Default: 10.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_AccL(lua_State *L);

/**
 * DecL - Set linear deceleration (mm/sec^2).
 *
 * Syntax (stub):
 *   DecL(deceleration)
 *
 * @param deceleration  Deceleration in mm/sec^2 (1-25000). Default: 10.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_DecL(lua_State *L);

/**
 * Accur - Set robot in-place accuracy mode.
 *
 * Syntax (stub):
 *   Accur(mode)
 *   Accur(mode, "CART")
 *
 * @param mode  One of: "HIGH", "STANDARD", "MEDIUM", "ROUGH", "MAXROUGH".
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_Accur(lua_State *L);

/* =========================================================================
 * Timing
 * ========================================================================= */

/**
 * DELAY - Delay program execution.
 *
 * Syntax:
 *   DELAY(delay_time)
 *
 * @param delay_time  Delay in seconds (minimum 0.001).
 *
 * On native builds: performs a real sleep.
 * On WASM builds: logs a warning and returns immediately (no-op).
 */
/* PUBLIC_INTERFACE */
int delta_DELAY(lua_State *L);

/**
 * WAIT - Wait for DI/DO signals or Modbus values.
 *
 * Syntax (stub):
 *   WAIT(io_type, io_index, status, timeout)
 *   WAIT(modbus_var, modbus_addr, data_type, modbus_data)
 *
 * Stub behaviour: logs a warning, returns immediately.
 */
/* PUBLIC_INTERFACE */
int delta_WAIT(lua_State *L);

/* =========================================================================
 * Points
 * ========================================================================= */

/**
 * SetGlobalPoint - Set/modify a global point in controller memory.
 *
 * Syntax (stub):
 *   SetGlobalPoint(point, point_name, x, y, z, ...)
 *
 * @param point       Point number (1-1000).
 * @param point_name  Point name string (must have "GL_" prefix).
 * @param ...         Coordinate and posture data.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_SetGlobalPoint(lua_State *L);

/**
 * ReadPoint - Read point information by item name.
 *
 * Syntax (stub):
 *   data = ReadPoint(point, item)
 *
 * @param point  Point name (string) or point number.
 * @param item   Item to read: "X","Y","Z","RX","RY","RZ","UF","TF","H","E","S","F","JRC".
 * @return       0.0 always in stub mode.
 *
 * Stub behaviour: logs a warning, returns 0.0.
 */
/* PUBLIC_INTERFACE */
int delta_ReadPoint(lua_State *L);

/* =========================================================================
 * Modbus
 * ========================================================================= */

/**
 * ReadModbus - Read a Modbus register value.
 *
 * Syntax (stub):
 *   data = ReadModbus(reg_address, size)
 *
 * @param reg_address  Memory address to read.
 * @param size         Data length: "W" (16-bit) or "DW" (32-bit).
 * @return             0 always in stub mode.
 *
 * Stub behaviour: logs a warning, returns 0.
 */
/* PUBLIC_INTERFACE */
int delta_ReadModbus(lua_State *L);

/**
 * WriteModbus - Write a value to a Modbus register.
 *
 * Syntax (stub):
 *   WriteModbus(reg_address, size, reg_value)
 *
 * @param reg_address  Memory address to write.
 * @param size         Data length: "W" (16-bit) or "DW" (32-bit).
 * @param reg_value    Value to write.
 *
 * Stub behaviour: logs a warning, does nothing.
 */
/* PUBLIC_INTERFACE */
int delta_WriteModbus(lua_State *L);

/* =========================================================================
 * Sockets
 * ========================================================================= */

/**
 * SocketClass - Create a TCP socket client object.
 *
 * Syntax (stub):
 *   variable = SocketClass(host_ip, port, spacing, delimiter, cmd, sleeptime, timeout)
 *
 * @param host_ip    IP address string.
 * @param port       Port number.
 * @param spacing    Receive delimiter char (or nil for default ',').
 * @param delimiter  Send end symbol (or nil for default '\r\n').
 * @param cmd        Default command string (or nil).
 * @param sleeptime  Interval between sends in seconds (or nil for 0.1s).
 * @param timeout    Receive timeout in seconds (or nil for 10s).
 * @return           Socket userdata table with Send, Receive, Close, CheckStatus methods.
 *
 * Stub behaviour: logs a warning, returns a stub userdata table.
 */
/* PUBLIC_INTERFACE */
int delta_SocketClass(lua_State *L);

/**
 * SocketServer - Create a TCP socket server object.
 *
 * Syntax (stub):
 *   SocketServer(port, spacing, delimiter, cmd, timeout)
 *
 * @param port       Port number for the server.
 * @param spacing    Receive delimiter char (or nil for ';').
 * @param delimiter  Send end symbol (or nil for '\r\n').
 * @param cmd        Default command (or nil).
 * @param timeout    Receive timeout in seconds (default 10s).
 * @return           Socket server stub userdata.
 *
 * Stub behaviour: logs a warning, returns a stub userdata table.
 */
/* PUBLIC_INTERFACE */
int delta_SocketServer(lua_State *L);

/**
 * CheckAllStatus - Read all socket connection statuses.
 *
 * Syntax (stub):
 *   ret_port[], ret_status[], ret_err[] = CheckAllStatus()
 *
 * @return  Three tables: ports, statuses, error codes. All empty in stub mode.
 *
 * Stub behaviour: logs a warning, returns three empty tables.
 */
/* PUBLIC_INTERFACE */
int delta_CheckAllStatus(lua_State *L);

/**
 * SocketVersion - Print the socket library version.
 *
 * Syntax (stub):
 *   SocketVersion()
 *
 * Stub behaviour: logs a warning, prints "stubbed/not connected".
 */
/* PUBLIC_INTERFACE */
int delta_SocketVersion(lua_State *L);

/* =========================================================================
 * Multi-task
 * ========================================================================= */

/**
 * AuxTasksAdd - Register subfunctions for cooperative multi-task execution.
 *
 * Syntax (stub):
 *   AuxTasksAdd(function1, function2, function3, ...)
 *
 * @param function1  Motion function (can use MovP, MovL, etc.).
 * @param function2+ Non-motion subfunctions.
 *
 * Stub behaviour: stores the functions, logs a warning.
 */
/* PUBLIC_INTERFACE */
int delta_AuxTasksAdd(lua_State *L);

/**
 * AuxTasks - Execute registered multi-task subfunctions.
 *
 * Syntax (stub):
 *   AuxTasks()
 *
 * Stub behaviour: calls each stored function once, logs a warning.
 */
/* PUBLIC_INTERFACE */
int delta_AuxTasks(lua_State *L);

/* =========================================================================
 * Utilities
 * ========================================================================= */

/**
 * split - Split a string by a delimiter into an array.
 *
 * Syntax:
 *   ret = split(str, pat)
 *
 * @param str  The string to split.
 * @param pat  The delimiter character or string.
 * @return     A Lua table (array) of substrings.
 *
 * Example:
 *   ret = split("123,A1,B1", ",")
 *   print(ret[1])  -- "123"
 *   print(ret[2])  -- "A1"
 */
/* PUBLIC_INTERFACE */
int delta_split(lua_State *L);

/**
 * Register all Delta API bindings into the Lua state.
 *
 * @param L  The Lua state.
 */
/* PUBLIC_INTERFACE */
void lu5_register_delta_api(lua_State *L);

/* Socket error constants */
#define DELTA_SOCKET_ERR_NONE              0x0000
#define DELTA_SOCKET_ERR_SESSION_INVALID   0x0001
#define DELTA_SOCKET_ERR_BUSY              0x0002
#define DELTA_SOCKET_ERR_SEND_FAIL         0x0003
#define DELTA_SOCKET_ERR_SENT_WITH_SBYTE   0x0006
#define DELTA_SOCKET_ERR_PACKET_TOO_SHORT  0x0007
#define DELTA_SOCKET_ERR_ROLE_INCORRECT    0x0008
#define DELTA_SOCKET_ERR_CONN_FULL         0x0009
#define DELTA_SOCKET_ERR_CHANNEL_ERROR     0x000A
#define DELTA_SOCKET_ERR_IP_PORT_ZERO      0x000B
#define DELTA_SOCKET_ERR_PORT_OUT_OF_RANGE 0x000C
#define DELTA_SOCKET_ERR_SOCKET_CREATE     0x000D
#define DELTA_SOCKET_ERR_BIND_FAIL         0x000E
#define DELTA_SOCKET_ERR_SETSOCKOPT        0x000F
#define DELTA_SOCKET_ERR_BIND              0x0010
#define DELTA_SOCKET_ERR_LISTEN            0x0011
#define DELTA_SOCKET_ERR_CONN_REFUSED      0x0012
#define DELTA_SOCKET_ERR_NO_END_CODE       0x0031

#endif /* __LU5_DELTA_API_BINDINGS__ */
