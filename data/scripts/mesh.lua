window = Window.new()
title = "Mesh Viewer 2000"
window:open(800, 600, title)

renderer = Renderer.new()
renderer:initialize()
renderer:set_background_color(Color.new(0, 1, 1, 1))

texture = ContentManager.load_texture2d("data/textures/error.png")

vertex_shader = ContentManager.load_shader("VertexShader", "data/shaders/gui_v.glsl")
fragment_shader = ContentManager.load_shader("FragmentShader", "data/shaders/gui_f.glsl")

shader_program = ContentManager.load_shaderprogram()
shader_program:add(vertex_shader)
shader_program:add(fragment_shader)
shader_program:link()

renderer:add_shaderprogram(shader_program)

last_time = os.time()
frames = 0

frametime = 0

mgr = GUIManager.new()
mgr:add_texture(texture)

texture:set_wrap("Repeat", "Repeat")

while window:is_open() do
    if window:is_key_down("escape") then
        window:close()
    elseif window:is_key_down("space") then
        renderer:set_background_color(Color.new(math.random(0, 1), math.random(0, 1), math.random(0, 1), math.random(0, 1))) 
    elseif window:is_key_down("f3") then
        renderer:set_wireframe(not renderer:get_wireframe())
    end

    frames = frames + 1

    if os.difftime(os.time(), last_time) >= 1 then
        frametime = 1000/frames
        window:set_title(title .. " || ms/frame: " .. frametime)
        frames = 0
        last_time = os.time()
    end

    renderer:draw()
    mgr:render()
    window:swap_buffers()
end
