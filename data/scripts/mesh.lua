window = Window.new()
title = "Mesh Viewer 2000"
window:open(800, 600, title)

renderer = Renderer.new()
renderer:set_background_color(Color.new(0, 1, 1, 1))

texture = ContentManager.load_texture2d("data/textures/error.png")

vertex_shader = ContentManager.load_shader("VertexShader", "data/shaders/vertex.glsl")
fragment_shader = ContentManager.load_shader("FragmentShader", "data/shaders/fragment.glsl")

shader_program = ContentManager.load_shaderprogram()
shader_program:add(vertex_shader)
shader_program:add(fragment_shader)
shader_program:link()

renderer:add_shaderprogram(shader_program)

last_time = os.time()
frames = 0

frametime = 0

while window:is_open() do
    if window:is_key_down("escape") then
        window:close()
    elseif window:is_key_down("space") then
        renderer:set_background_color(Color.new(math.random(0, 1), math.random(0, 1), math.random(0, 1), math.random(0, 1))) 
    end

    frames = frames + 1

    if os.difftime(os.time(), last_time) >= 1 then
        frametime = 1000/frames
        window:set_title(title .. " || ms/frame: " .. frametime)
        frames = 0
        last_time = os.time()
    end

    renderer:draw()
    window:swap_buffers()
end
