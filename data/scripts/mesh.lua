window = Window.new(800, 600, "MeshViewer")
renderer = Renderer.new()

renderer:set_background_color(Color.new(0, 1, 1, 1))

texture = ContentManager.load("Texture2D", "data/textures/error.png")

while window:is_open() do
    if window:is_key_down("escape") then
        window:close()
    elseif window:is_key_down("space") then
        renderer:set_background_color(Color.new(math.random(0, 1), math.random(0, 1), math.random(0, 1), math.random(0, 1))) 
    end

    renderer:draw()
    window:swap_buffers()
end
