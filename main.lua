window = Window.new(800, 600, "MuggEngine Window")
window:set_vsync(true)

input = InputHandler.new()

start_time = os.time()

last_time = os.clock()
frames = 0

renderer = Renderer.new()

shader_program = ShaderProgram.new("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")
shader_program:link()

renderer:add_shader_program(shader_program)

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

backgroundColor = Color.new()

function update()
    if input:is_key_down("Escape") == true and window:is_focused() == true then
        window:close()
    end
    
    if input:is_key_down("Space") == true then
        backgroundColor:set_colors(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1)
    end
    
    frames = frames + 1

    if (os.clock() - last_time) >= 1 then
        print(1000/frames .. " ms/frame")
        frames = 0
        last_time = os.time()
    end
end

function render()
    renderer:set_background_color(backgroundColor)

    renderer:begin_render(window:get_resolution_x(), window:get_resolution_y())
    -----------------------
    -- Render stuff here --
    -----------------------
    renderer:end_render()

    window:swap_buffers()
end

while window:is_open() == true do
    update()
    render()
end

print("Program ran for " .. os.difftime(os.time(), start_time) .. " seconds.")
