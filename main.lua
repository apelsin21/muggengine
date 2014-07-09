window = Window.new(800, 600, "Client")

client = Client.new()
client:initialize(2, 0, 0)

renderer = Renderer.new()
renderer:initialize()

while window:is_open() do
    if client:is_connected() then
        renderer:set_background_color(Color.new(0, 1, 0, 1))
    else
        renderer:set_background_color(Color.new(0, 0, 0, 1))
    end

    if window:is_key_down("escape") then
        window:close()
    end
    if window:is_key_down("delete") then
        if client:is_connected() == false then
            client:connect("127.0.0.1", 2300, 3000)
        else
            client:disconnect(3000)
        end
    end

    client:poll(0)

    renderer:draw()
    window:swap_buffers()
end

client:disconnect(3000)
