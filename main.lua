Window.create(800, 600, 0, 0, "MuggEngine Window", false)

start_time = os.time()


vertex_shader = Shader.new("VertexShader", "data/shaders/vertex.glsl")
fragment_shader = Shader.new("FragmentShader", "data/shaders/fragment.glsl")

shader_program = ShaderProgram.new()

shader_program:add_shader(vertex_shader)
shader_program:add_shader(fragment_shader)

shader_program:link()

Renderer.add_shader_program(shader_program)

backgroundColor = Color.new()

last_time = os.time()
deltatime = 0
frames = 0

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

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

    frames = frames + 1
    
    if os.difftime(os.time(), last_time) >= 1 then
        Window.set_title("Running time: " .. os.difftime(os.time(), start_time) .. ", ms/frame: " .. 1000/frames)
        frames = 0
        last_time = last_time + 1;
    end
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
