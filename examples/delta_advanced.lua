--[[
  delta_advanced.lua
  Delta API example: Points, Modbus, Sockets, and Cooperative Multi-tasks.

  Demonstrates:
    - SetGlobalPoint / ReadPoint
    - ReadModbus / WriteModbus
    - SocketClass / SocketServer / CheckAllStatus / SocketVersion
    - AuxTasksAdd / AuxTasks
    - split utility function

  All functions are safe stubs – no hardware is required.
--]]

print("=== Delta API: Advanced Example (Points + Modbus + Sockets + Tasks) ===")

-- ============================================================
-- 1. Global Points
-- ============================================================
print("\n--- Global Points ---")

-- Set a six-axis global point (GL_P1) at position (200, 100, -150)
SetGlobalPoint(1, "GL_P1", 200, 100, -150, 0, 0, 0, 0, 0, 0, 0, {0,0,0,1,0,0,0,4})
print("SetGlobalPoint(1, 'GL_P1', ...) called")

-- Read point 1 X coordinate
local x = ReadPoint(1, "X")
print("ReadPoint(1, 'X') =", x)

-- Read point 1 Z coordinate
local z = ReadPoint(1, "Z")
print("ReadPoint(1, 'Z') =", z)

-- ============================================================
-- 2. Modbus
-- ============================================================
print("\n--- Modbus ---")

-- Read a 16-bit register at address 0x1010
local val_w = ReadModbus(0x1010, "W")
print("ReadModbus(0x1010, 'W') =", val_w)

-- Read a 32-bit register at address 0x1012 (even address for DW)
local val_dw = ReadModbus(0x1012, "DW")
print("ReadModbus(0x1012, 'DW') =", val_dw)

-- Write a value to register 0x1010
WriteModbus(0x1010, "W", 42)
print("WriteModbus(0x1010, 'W', 42) called")

-- ============================================================
-- 3. Sockets
-- ============================================================
print("\n--- Sockets ---")

-- Print the socket version (stub)
SocketVersion()

-- Create a socket client connecting to 192.168.1.99:21
local sock = SocketClass("192.168.1.99", 21, nil, "\r\n", nil, 0.3, 5)
print("SocketClass created:", sock)

-- Send data
sock:Send("hello")
print("sock:Send('hello') called")

-- Receive data (returns empty table in stub mode)
local data = sock:Receive()
print("sock:Receive() returned table of length:", #data)

-- Check connection status
local port, status, err = sock:CheckStatus()
print("sock:CheckStatus() port=" .. tostring(port)
      .. " status=" .. tostring(status)
      .. " err=" .. tostring(err))

-- Close the connection
sock:Close()
print("sock:Close() called")

-- Create a socket server on port 7000
local server = SocketServer(7000, ";", "*", nil, 10)
print("SocketServer created:", server)

-- Check all connection statuses
local ports, statuses, errors = CheckAllStatus()
print("CheckAllStatus() returned", #ports, "entries")

-- ============================================================
-- 4. String split utility
-- ============================================================
print("\n--- split utility ---")

local csv = "123,A1,B1,C2"
local parts = split(csv, ",")
print("split('123,A1,B1,C2', ','):")
for i, v in ipairs(parts) do
    print("  [" .. i .. "] = " .. v)
end

-- ============================================================
-- 5. Cooperative Multi-task (AuxTasksAdd / AuxTasks)
-- ============================================================
print("\n--- Multi-task (AuxTasksAdd / AuxTasks) ---")

-- Define motion and output subfunctions
function MotionTask()
    MovP(1)
    MovP(2)
    MovP(3)
end

function OutputTask1()
    DO(1, "ON")
    DO(1, "OFF")
end

function OutputTask2()
    DO(2, "ON")
    DO(2, "OFF")
end

-- Register subfunctions for cooperative execution
AuxTasksAdd(MotionTask, OutputTask1, OutputTask2)
print("AuxTasksAdd(MotionTask, OutputTask1, OutputTask2) called")

-- Run one iteration of cooperative tasks
-- (in a real program this would be inside a while loop)
AuxTasks()
print("AuxTasks() iteration complete")

-- ============================================================
-- 6. Socket error constants
-- ============================================================
print("\n--- Socket Error Constants ---")
print("SOCKET_ERR_NONE              =", SOCKET_ERR_NONE)
print("SOCKET_ERR_CONN_REFUSED      =", SOCKET_ERR_CONN_REFUSED)
print("SOCKET_ERR_PORT_OUT_OF_RANGE =", SOCKET_ERR_PORT_OUT_OF_RANGE)

print("\n=== Advanced Example Complete ===")
