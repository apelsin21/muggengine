window = Window.new(800, 600, "MeshViewer")
renderer = Renderer.new()

mesh = Mesh.new("data/models/complexshape.nff")

renderer:set_background_color(Color.new(0, 1, 1, 1))

while window:is_open() do
    if window:is_key_down("escape") then
        window:close()
    end

    renderer:draw()
    window:swap_buffers()
end
