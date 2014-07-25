window = Window.new()
window:open(800, 600, "MuggEngine")

renderer = Renderer.new()
renderer:set_background_color(Color.new(0, 1, 1, 1))

texture = ContentManager.load_texture2d("data/textures/error.png")

print("Error.png has a resolution of: " .. texture:get_width() .. "x" .. texture:get_height() .. " and a bpp of: " .. texture:get_bpp())

vertex_shader = ContentManager.load_shader("VertexShader", "data/shaders/vertex.glsl")
fragment_shader = ContentManager.load_shader("FragmentShader", "data/shaders/fragment.glsl")

while window:is_open() do
    if window:is_key_down("escape") then
        window:close()
    elseif window:is_key_down("space") then
        renderer:set_background_color(Color.new(math.random(0, 1), math.random(0, 1), math.random(0, 1), math.random(0, 1))) 
    end

    renderer:draw()
    window:swap_buffers()
end
