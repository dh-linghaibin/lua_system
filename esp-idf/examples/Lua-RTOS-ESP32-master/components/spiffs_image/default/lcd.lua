

-- create fontdemo table and set some defaults
tftdemo = {
    dispType = gdisplay.SSD1306_128_32, -- or gdisplay.ST7735B, gdisplay.ST7735, gdisplay.ST7735G
    maxx = 128,
    maxy = 32,
    miny = 1,
    touch = false,
    -- fonts used in this demo
    fontnames = {
        gdisplay.FONT_DEFAULT,
        gdisplay.FONT_7SEG,
        gdisplay.FONT_UBUNTU16,
        gdisplay.FONT_COMIC24,
        gdisplay.FONT_TOONEY32,
        gdisplay.FONT_MINYA24
    },
    -- images used in this demo {file_name, width, height}
    -- width & height are needed only for raw images
    images = {
        jpg = {"tiger240.jpg", 0, 0},
        bmp = {"tiger.bmp", 0, 0}
    }
}

-- Init the display
function tftdemo.init()
    if gdisplay.gettype() < 0 then
        gdisplay.init(tftdemo.dispType, gdisplay.LANDSCAPE_FLIP)
        if gdisplay.gettype() < 0 then
            print("LCD not initialized")
            return false
        end
        -- if gdisplay.gettype() ~= gdisplay.SSD1306_128_32 then
        --     tftdemo.touch = false
        -- end
    end
    return true
end




thread.start(function()
    tftdemo.init();
    print("lcd init")
    -- gdisplay.ellipse(0,0,20,20,GDISPLAY_WHITE)
    gdisplay.clear()
    gdisplay.setfont(gdisplay.FONT_7SEG)
    num = 1000;
    num = num + 1;
    gdisplay.write({0,0},tostring(num))
    while true do
        tmr.delayms(300)
        gdisplay.clear()
        num = num + 1;
        gdisplay.write({0,0},tostring(num))
        -- print(num);
    end
end)