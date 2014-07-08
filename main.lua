title = "MuggEngine Window"
window = Window.new(800, 600, title)

start_time = os.time()

shader_program = ShaderProgram.new()
shader_program:load_shader("VertexShader", "data/shaders/vertex.glsl")
shader_program:load_shader("FragmentShader", "data/shaders/fragment.glsl")
shader_program:link()

renderer = Renderer.new()

renderer:initialize()

renderer:add_shader_program(shader_program)

texture = Texture2D.new()
texture:load("data/textures/test.png", "Repeat", "Nearest", false)

last_time = os.time()
frames = 0

client = Client.new()
client:initialize(2, 0, 0)

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

function update()
    frames = frames + 1

    if window:is_key_down("escape") then
        window:close()
    end
    
    if window:is_key_down("space") then
        renderer:set_background_color(Color.new(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1))
    end

    if os.difftime(os.time(), last_time) >= 1 then
        window:set_title(title .. " || time: " .. os.difftime(os.time(), start_time) .. " || ms/frame: " .. 1000/frames)
        frames = 0
        last_time = last_time + 1;
    end

    if client:is_connected() == false then
        client:connect("192.168.1.91", 8080, 5000)
    else
        if window:is_key_down("enter") then
            client:disconnect(3000)
        end
    end

    client:poll(0)
end

function render()

    if window:is_focused() then
        renderer:render()
    end

    window:swap_buffers()
end

while window:is_open() do
    update()
    render()
end
