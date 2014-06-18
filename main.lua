window = Window.new(800, 600, "MuggEngine Window")

input = InputHandler.new()

start_time = os.time()

renderer = Renderer.new()

shader_program = ShaderProgram.new("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")
shader_program:link()

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

backgroundColor = Color.new()

last_time = os.clock()
fps = 0
deltatime = 0

function update()
    if window:is_focused() == true then
        if input:is_key_down("Escape") == true then
            window:close()
        end
        
        if input:is_key_down("Space") == true then
            backgroundColor:set_colors(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1)
            renderer:set_background_color(backgroundColor)
        end
    end

    deltatime = (os.clock() - last_time)
    fps = 1/deltatime
    last_time = os.clock()
    window:set_title("Time: " .. os.difftime(os.time(), start_time) .. " s, ms/frame: " .. fps)
end

function render()
    renderer:begin_render(window:get_resolution_x(), window:get_resolution_y())
    renderer:end_render()
    
    window:swap_buffers()
end

while window:is_open() == true do
    update()
    render()

end

print("Program ran for " .. os.difftime(os.time(), start_time) .. " seconds.")
