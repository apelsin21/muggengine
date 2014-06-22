Window.create(800, 600, 0, 0, "MuggEngine Window", false)

start_time = os.time()

shader_program = ShaderProgram.new()
shader_program:load_shader("VertexShader", "data/shaders/vertex.glsl")
shader_program:load_shader("FragmentShader", "data/shaders/fragment.glsl")
shader_program:link()

Renderer.initialize()

Renderer.add_shader_program(shader_program)

last_time = os.time()
deltatime = 0
frames = 0

texture = Texture2D.new("data/textures/test.png")

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

function update()
    if Window.is_focused() == true then
        if InputHandler.is_key_down("Escape") == true then
            Window.close()
        end

        if InputHandler.is_key_down("Space") == true then
            Renderer.set_background_color(Color.new(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1))
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
