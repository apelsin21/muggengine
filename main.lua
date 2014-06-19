Window.create(800, 600, 0, 0, "MuggEngine Window", false)

start_time = os.time()

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
    if Window.is_focused() == true then
        if InputHandler.is_key_down("Escape") == true then
            Window.close()
        end

        if InputHandler.is_key_down("Space") == true then
            backgroundColor:set_colors(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1)
            Renderer.set_background_color(backgroundColor)
        end
    end

    deltatime = (os.clock() - last_time)
    fps = 1/deltatime
    last_time = os.clock()

    Window.set_title(fps)
end

function render()
    Renderer.begin_render(Window.get_resolution_x(), Window.get_resolution_y())
    Renderer.end_render()
    
    Window.swap_buffers()
end

while Window.is_open() == true do
    update()
    render()
end

print("Running time: " .. os.difftime(os.time(), start_time))
