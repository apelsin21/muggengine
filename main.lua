window = Window.new(800, 600, "MuggEngine Window")
window:set_vsync(true)

input = InputHandler.new()

start_time = os.time()

last_time = os.clock()
frames = 0

renderer = Renderer.new()

shader_program = ShaderProgram.new("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")
shader_program:link()

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

backgroundColor = Color.new()

while window:is_open() == true do
    if input:is_key_down("Escape") == true and window:is_focused() == true then
        window:close()
    end

    current_time = os.clock()
    frames = frames + 1

    if input:is_key_down("F11") == true then
        backgroundColor:set_colors(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1)
    end

    if(current_time-last_time) >= 1 then
        print(1000/frames .. " ms/frame")
        
        
        frames = 0
        last_time = current_time
    end

    renderer:set_background_color(backgroundColor)

    renderer:begin_render(window:get_resolution_x(), window:get_resolution_y())
    renderer:end_render()

    window:swap_buffers()
end

print("Program ran for " .. os.difftime(os.time(), start_time) .. " seconds.")
