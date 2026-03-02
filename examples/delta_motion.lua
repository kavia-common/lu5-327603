--[[
  delta_motion.lua
  Delta API example: Motion, speed/acceleration settings, and timing.

  Demonstrates MovP, MovL, MovJ, SpdJ/SpdL, AccJ/AccL, DecJ/DecL,
  Accur, DELAY, and WAIT in a typical robot move sequence.
  All functions are safe stubs – no hardware is required.
--]]

print("=== Delta API: Motion + Speed/Accel + Timing Example ===")

-- Configure joint motion parameters
SpdJ(15)       -- Set max joint speed to 15%
AccJ(10)       -- Set joint acceleration to 10%
DecJ(10)       -- Set joint deceleration to 10%
print("Joint speed/accel/decel set")

-- Configure linear motion parameters
SpdL(200)      -- Set max linear speed to 200 mm/sec
AccL(100)      -- Set linear acceleration to 100 mm/sec^2
DecL(100)      -- Set linear deceleration to 100 mm/sec^2
print("Linear speed/accel/decel set")

-- Set in-place accuracy mode
Accur("HIGH")
print("Accuracy mode: HIGH")

-- Define a simple point sequence (point numbers 1, 2, 3)
-- In a real controller these would be stored global points.

-- Move to point 1 using point-to-point motion
print("Moving to point 1 (MovP)...")
MovP(1)

-- Wait for DI signal or 2000ms timeout before next move
WAIT("DI", 1, "ON", 2000)

-- Delay 0.5 seconds
print("Delaying 0.5s...")
DELAY(0.5)

-- Move to point 2 with linear motion
print("Moving to point 2 (MovL)...")
MovL(2)

-- Move axis 3 (joint 3) to -90 degrees
print("Rotating joint 3 to -90 degrees (MovJ)...")
MovJ(3, -90)

-- Delay 1 second before returning
DELAY(1.0)

-- Move back to point 1
print("Returning to point 1 (MovP)...")
MovP(1)

print("=== Motion Example Complete ===")
