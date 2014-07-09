window = Window.new(800, 600, "Client")

client = Client.new()
client:initialize(2, 0, 0)

renderer = Renderer.new()
renderer:initialize()

while window:is_open() do
    if client:is_connected() == false then
        client:connect("192.168.1.91", 2300, 5000)
    else
        renderer:set_background_color(Color.new(0, 1, 0, 1))
    end

    if window:is_key_down("escape") then
        window:close()
    end

    client:poll(0)

    renderer:draw()
    window:swap_buffers()
end

client:disconnect(3000)
