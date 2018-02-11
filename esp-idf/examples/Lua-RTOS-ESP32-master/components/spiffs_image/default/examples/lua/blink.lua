-- ----------------------------------------------------------------
-- WHITECAT ECOSYSTEM
--
-- Lua RTOS examples
-- ----------------------------------------------------------------
-- Read blink a led in a thread. While led is blinking Lua
-- interpreter are available, you cant start new threads for
-- doing other things.
-- ----------------------------------------------------------------

thread.start(function()
  pio.pin.setdir(pio.OUTPUT, pio.GPIO25)
  pio.pin.setpull(pio.NOPULL, pio.GPIO25)
  while true do
    pio.pin.setval(1, pio.GPIO25)
    tmr.delayms(100)
    pio.pin.setval(0, pio.GPIO25)
    tmr.delayms(100)
  end
end)
