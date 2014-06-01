title = "MuggEngine Lua window"

window = Window.new(800, 600, title)
window:set_vsync(true)

input = InputHandler.new()

start_time = os.clock()

while window:is_open() == true do
    if input:is_key_down("Escape") == true then
        window:close()
    end

    current_time = os.clock()
    delta_time = current_time - start_time
    start_time = current_time

    window:set_title(title .. " FPS: " .. 60 / delta_time)

    window:swap_buffers()
end
