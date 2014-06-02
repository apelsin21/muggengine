title = "MuggEngine Lua window"

window = Window.new(800, 600, title)
window:set_vsync(true)

input = InputHandler.new()

last_time = os.clock()
frames = 0

while window:is_open() == true do
    if input:is_key_down("Escape") == true then
        window:close()
    end

    current_time = os.clock()
    frames = frames + 1

    if(current_time - last_time) >= 1 then
        print(1000/frames .. " ms/frame")
        frames = 0
        last_time = current_time
    end

    window:swap_buffers()
end
