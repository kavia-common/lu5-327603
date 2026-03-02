# Delta API Reference

lu5 includes a **Delta Robot Controller-compatible Lua API** as safe stubs.  
These bindings mirror the Delta DRS-series robot language specification so that
Lua scripts written for Delta controllers can be loaded and tested in lu5 without
real hardware.

> **Stub behaviour:** Every function in this API logs a `WARN` message indicating
> `"stubbed/not connected"` and returns a sensible default.  No function crashes
> or raises a Lua error due to missing hardware.

---

## Platform Caveats

| Feature | Linux (native) | Windows (MinGW/MSYS2) | WASM (wasm32-wasi) |
|---|---|---|---|
| `DELAY` | Real `nanosleep` sleep | Real `Sleep` (Windows API) | No-op + warning |
| Sockets | Stub (no real TCP) | Stub (WinSock linked via `-lws2_32`) | Stub |
| All others | Stub + warn | Stub + warn | Stub + warn |

> **Windows note:** The Makefile links `-lws2_32` for all Windows builds so that
> socket-related code compiles without linker errors.

---

## Groups

- [Digital I/O](#digital-io)
- [Motion](#motion)
- [Speed / Accel / Accuracy](#speed--accel--accuracy)
- [Timing](#timing)
- [Points](#points)
- [Modbus](#modbus)
- [Sockets](#sockets)
- [Multi-task](#multi-task)
- [Utilities](#utilities)

---

## Digital I/O

### `DI(pin_index)` → `"ON"` | `"OFF"`
### `DI(pin_index, length)` → `number`

Read the status of a standard digital input pin.

| Parameter | Type | Description |
|---|---|---|
| `pin_index` | number or string | Pin number (1–24) or IO name |
| `length` | number (optional) | Number of pins to read (1–24) |

**Stub return:** `"OFF"` for single pin; `0` for multi-pin numeric reads.

```lua
local s = DI(1)         -- "OFF"
local n = DI(1, 4)      -- 0
```

---

### `DO(pin_index, status [, delay_time])`
### `DO(pin_index, length, status_num [, delay_time])`

Set the state of a standard digital output pin.

| Parameter | Type | Description |
|---|---|---|
| `pin_index` | number or string | Pin number (1–12) or IO name |
| `status` | string | `"ON"` or `"OFF"` |
| `delay_time` | number (optional) | Delay in seconds before output reverses |
| `length` | number | Number of pins (multi-pin form) |
| `status_num` | number | Bitmask for multi-pin form |

**Stub:** does nothing, emits a warning.

```lua
DO(1, "ON")
DO(2, "OFF", 0.5)
```

---

### `ExtDI(address_index, pin_index)` → `"ON"` | `"OFF"`

Read a digital input on an external board (DMCNET).

**Stub return:** `"OFF"`.

```lua
local s = ExtDI(4, 1)
```

---

### `ExtDO(address_index, pin_index, status [, delay_time])`

Set a digital output on an external board (DMCNET).

**Stub:** does nothing, emits a warning.

```lua
ExtDO(4, 2, "ON")
ExtDO(4, 3, "OFF", 1.0)
```

---

## Motion

### `MovP(point)`

Point-to-point motion to a target point.

| Parameter | Type | Description |
|---|---|---|
| `point` | string or number | Point name or number |

**Stub:** does nothing, emits a warning.

```lua
MovP(1)
MovP("GL_Home")
```

---

### `MovL(point)`

Linear motion to a target point.

**Stub:** does nothing, emits a warning.

```lua
MovL(2)
```

---

### `MovJ(joint, degree)`

Rotate a single robot axis to a target angle.

| Parameter | Type | Description |
|---|---|---|
| `joint` | number | Axis number (1–6) |
| `degree` | number | Target angle in degrees (−360 to 360) |

**Stub:** does nothing, emits a warning.

```lua
MovJ(3, -90)
```

---

## Speed / Accel / Accuracy

### `SpdJ(speed)`

Set maximum joint speed (%).  
Default: 10 %.

```lua
SpdJ(20)
```

---

### `AccJ(acceleration)`

Set joint acceleration (%).  
Default: 10 %.

```lua
AccJ(15)
```

---

### `DecJ(deceleration)`

Set joint deceleration (%).  
Default: 10 %.

```lua
DecJ(15)
```

---

### `SpdL(speed)`

Set maximum linear speed (mm/sec).  
Default: 100 mm/sec.

```lua
SpdL(500)
```

---

### `AccL(acceleration)`

Set linear acceleration (mm/sec²).  
Default: 10 mm/sec².

```lua
AccL(200)
```

---

### `DecL(deceleration)`

Set linear deceleration (mm/sec²).  
Default: 10 mm/sec².

```lua
DecL(200)
```

---

### `Accur(mode [, "CART"])`

Set the robot in-place accuracy mode.

| Mode | Description |
|---|---|
| `"HIGH"` | Highest accuracy, longest settling time |
| `"STANDARD"` | 10× HIGH range |
| `"MEDIUM"` | 100× HIGH range |
| `"ROUGH"` | 200× HIGH range |
| `"MAXROUGH"` | 2000× HIGH range |

```lua
Accur("HIGH")
Accur("ROUGH", "CART")
```

---

## Timing

### `DELAY(delay_time)`

Delay program execution.

| Parameter | Type | Description |
|---|---|---|
| `delay_time` | number | Delay in seconds (minimum 0.001) |

**Platform behaviour:**
- **Linux / Windows (native):** performs a real sleep.
- **WASM:** logs a warning and returns immediately (no-op).

```lua
DELAY(0.5)   -- delay 500 ms
DELAY(2)     -- delay 2 s
```

---

### `WAIT(io_type, io_index, status [, timeout])`
### `WAIT(modbus_var, modbus_addr, data_type, modbus_data)`

Wait for a DI/DO condition or a Modbus register value.

**Stub:** returns immediately, emits a warning.

```lua
WAIT("DI", 1, "ON")
WAIT("DI", 1, "ON", 2000)
```

---

## Points

### `SetGlobalPoint(point, point_name, x, y, z, ...)`

Store a global point in controller memory.

| Parameter | Type | Description |
|---|---|---|
| `point` | number | Point number (1–1000) |
| `point_name` | string | Must have `"GL_"` prefix |
| `x, y, z` | number | Cartesian position (mm) |
| `...` | varies | Rotation, posture, UF, TF, JRC data |

**Stub:** does nothing, emits a warning.

```lua
SetGlobalPoint(1, "GL_P1", 200, 100, -150, 0, 0, 0, 0, 0, 0, 0)
```

---

### `ReadPoint(point, item)` → `number`

Read a specific data item from a point.

| `item` value | Description |
|---|---|
| `"X"`, `"Y"`, `"Z"` | Cartesian coordinates (mm) |
| `"RX"`, `"RY"`, `"RZ"` | Rotation angles (degrees) |
| `"UF"`, `"TF"` | User/Tool frame |
| `"H"`, `"E"`, `"S"`, `"F"` | Posture flags |
| `"JRC"` | Joint rotation count table |

**Stub return:** `0.0`.

```lua
local x = ReadPoint(1, "X")
local z = ReadPoint("GL_P1", "Z")
```

---

## Modbus

### `ReadModbus(reg_address, size)` → `number`

Read a value from a Modbus register.

| Parameter | Type | Description |
|---|---|---|
| `reg_address` | number | Memory address |
| `size` | string | `"W"` (16-bit) or `"DW"` (32-bit, even address) |

**Stub return:** `0`.

```lua
local v = ReadModbus(0x1010, "W")
```

---

### `WriteModbus(reg_address, size, reg_value)`

Write a value to a Modbus register.

**Stub:** does nothing, emits a warning.

```lua
WriteModbus(0x1010, "W", 100)
```

---

## Sockets

> **Note:** These are stub implementations. No real TCP connection is made.  
> On Windows, `-lws2_32` is linked automatically to support WinSock.

### `variable = SocketClass(host_ip, port, spacing, delimiter, cmd, sleeptime, timeout)`

Create a TCP socket client.

| Parameter | Default | Description |
|---|---|---|
| `host_ip` | — | Server IP address string |
| `port` | — | Port number |
| `spacing` | `','` | Receive data split character |
| `delimiter` | `'\r\n'` | Send end-of-message character |
| `cmd` | nil | Default command |
| `sleeptime` | 0.1 s | Interval between sends |
| `timeout` | 10 s | Receive timeout |

Returns a socket **userdata** with methods: `Send`, `Receive`, `Close`, `CheckStatus`.

```lua
local sock = SocketClass("192.168.1.99", 21, nil, "\r\n", nil, 0.3, 5)
sock:Send("hello")
local data = sock:Receive()
sock:Close()
```

---

### `SocketServer(port, spacing, delimiter, cmd, timeout)`

Create a TCP socket server.

Returns the same userdata interface as `SocketClass`.

```lua
local srv = SocketServer(7000, ";", "*", nil, 10)
```

---

### `ret_port[], ret_status[], ret_err[] = CheckAllStatus()`

Read all channel connection statuses.

**Stub return:** three empty tables.

```lua
local ports, statuses, errors = CheckAllStatus()
```

---

### `SocketVersion()`

Print the socket library version.

**Stub:** prints `"stubbed/not connected"`.

---

### Socket Error Constants

| Constant | Value | Description |
|---|---|---|
| `SOCKET_ERR_NONE` | 0x0000 | No error |
| `SOCKET_ERR_SESSION_INVALID` | 0x0001 | SessionID invalid/conflict |
| `SOCKET_ERR_BUSY` | 0x0002 | Busy |
| `SOCKET_ERR_SEND_FAIL` | 0x0003 | Send fail, disconnect |
| `SOCKET_ERR_SENT_WITH_SBYTE` | 0x0006 | Sent with SByte/EByte set |
| `SOCKET_ERR_PACKET_TOO_SHORT` | 0x0007 | Packet too short |
| `SOCKET_ERR_ROLE_INCORRECT` | 0x0008 | Freeport role incorrect |
| `SOCKET_ERR_CONN_FULL` | 0x0009 | Connection full |
| `SOCKET_ERR_CHANNEL_ERROR` | 0x000A | Channel error |
| `SOCKET_ERR_IP_PORT_ZERO` | 0x000B | IP or Port is zero |
| `SOCKET_ERR_PORT_OUT_OF_RANGE` | 0x000C | Port out of range (3000–10000) |
| `SOCKET_ERR_SOCKET_CREATE` | 0x000D | Cannot create socket |
| `SOCKET_ERR_BIND_FAIL` | 0x000E | Network device bind failed |
| `SOCKET_ERR_SETSOCKOPT` | 0x000F | setsockopt SO_REUSEADDR error |
| `SOCKET_ERR_BIND` | 0x0010 | Server bind failed |
| `SOCKET_ERR_LISTEN` | 0x0011 | Server listen failed |
| `SOCKET_ERR_CONN_REFUSED` | 0x0012 | Connection refused |
| `SOCKET_ERR_NO_END_CODE` | 0x0031 | Server data missing end code |

---

## Multi-task

### `AuxTasksAdd(function1, function2, ...)`

Register up to 10 subfunctions for cooperative multi-task execution.

- `function1` may contain motion commands (MovP, MovL, MovJ, …).
- `function2+` must not contain motion commands.

**Stub:** stores the functions; `AuxTasks()` will call each one in sequence.

```lua
AuxTasksAdd(MotionTask, OutputTask1, OutputTask2)
```

---

### `AuxTasks()`

Execute one cooperative round of all registered subfunctions.

Each subfunction runs for approximately 15 ms in a real controller.  
In stub mode, each function is called once per `AuxTasks()` invocation.

```lua
while true do
    AuxTasks()
end
```

---

## Utilities

### `ret = split(str, pat)` → table

Split a string by a delimiter and return the parts as a Lua array.

| Parameter | Type | Description |
|---|---|---|
| `str` | string | Input string to split |
| `pat` | string or char | Delimiter |

```lua
local parts = split("123,A1,B1", ",")
-- parts[1] = "123"
-- parts[2] = "A1"
-- parts[3] = "B1"
```

---

## Full Example

See the example scripts for working demonstrations:

- [`examples/delta_io.lua`](../examples/delta_io.lua) — Digital I/O
- [`examples/delta_motion.lua`](../examples/delta_motion.lua) — Motion + Speed/Accel + Timing
- [`examples/delta_advanced.lua`](../examples/delta_advanced.lua) — Points + Modbus + Sockets + Tasks
