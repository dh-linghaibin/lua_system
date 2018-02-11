-- ----------------------------------------------------------------
-- WHITECAT ECOSYSTEM
--
-- Lua RTOS examples
-- ----------------------------------------------------------------
-- Read blink a led in a thread. While led is blinking Lua
-- interpreter are available, you cant start new threads for
-- doing other things.
-- ----------------------------------------------------------------
require("module")

local function NumToCN(num)
    local size = #tostring(num)
    local CN = ""
    local StrCN = {"一","二","三","四","五","六","七","八","九"}
    for i = 1 , size do
        CN = CN .. StrCN[tonumber(string.sub(tostring(num), i , i))]
    end
    return CN
end

function callback()
  print "Callback"
end

function defcallback()
  print "Predef callback"
end

thread.start(function()

  haha.setnotify(callback)
  haha.testnotify()

  -- haha.setnotify(callback)

  print(module.constant)
  module.func3()
  print(NumToCN(56665))
  pio.pin.setdir(pio.OUTPUT, pio.GPIO25)
  pio.pin.setpull(pio.NOPULL, pio.GPIO25)
  while true do
    pio.pin.setval(1, pio.GPIO25)
    tmr.delayms(200)
    pio.pin.setval(0, pio.GPIO25)
    tmr.delayms(200)
  end
end)

-- thread.start(function()
-- 	while true do
-- 		print("linghaibin")
-- 		tmr.delayms(300)
-- 	end
-- end)

