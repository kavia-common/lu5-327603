--[[
  delta_io.lua
  Delta API example: Digital I/O operations.

  Demonstrates the use of DI, DO, ExtDI, and ExtDO.
  All functions are safe stubs – no hardware is required.
  A WARN message is printed for each call indicating the stub behaviour.
--]]

print("=== Delta API: Digital I/O Example ===")

-- Read a standard digital input (pin 1)
-- Returns "OFF" in stub mode
local status = DI(1)
print("DI(1) status:", status)

-- Read multiple digital inputs (pins 1-4 as a numeric bitmask)
local status_num = DI(1, 4)
print("DI(1, 4) numeric status:", status_num)

-- Set a standard digital output (pin 2 → ON)
DO(2, "ON")
print("DO(2, ON) called")

-- Set digital output with a 0.5s delay
DO(3, "OFF", 0.5)
print("DO(3, OFF, 0.5) called")

-- Read external board digital input (board station 4, pin 1)
local ext_status = ExtDI(4, 1)
print("ExtDI(4, 1) status:", ext_status)

-- Set external board digital output (board station 4, pin 2 → ON)
ExtDO(4, 2, "ON")
print("ExtDO(4, 2, ON) called")

-- Set external board digital output with delay
ExtDO(4, 3, "OFF", 1.0)
print("ExtDO(4, 3, OFF, 1.0) called")

print("=== Digital I/O Example Complete ===")
