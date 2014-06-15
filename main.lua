window = Window.new(800, 600, "MuggEngine Window")

input = InputHandler.new()

start_time = os.time()

last_time = os.clock()
frames = 0

renderer = Renderer.new()

shader_program = ShaderProgram.new("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")
shader_program:link()

while window:is_open() == true do
    if input:is_key_down("Escape") == true and window:is_focused() == true then
        window:close()
    end

    current_time = os.clock()
    frames = frames + 1

    if input:is_key_down("F11") == true then
        if window:get_fullscreen() == true then
            window:set_fullscreen(false)
        else
            window:set_fullscreen(true)
        end
    end

    if(current_time-last_time) >= 1 then
        print(1000/frames .. " ms/frame")
        frames = 0
        last_time = current_time
    end

    renderer:begin_render(window:get_resolution_x(), window:get_resolution_y())
    renderer:end_render()

    window:swap_buffers()
end

print("Program ran for " .. os.difftime(os.time(), start_time) .. " seconds.")
