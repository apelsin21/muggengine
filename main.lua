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

print("Texture has ID: " .. texture:get_gl_id() .. ", filepath: " .. texture:get_filepath() .. ", resolution: " .. texture:get_width() .. "x" .. texture:get_height() .. ", bpp: " .. texture:get_bpp() .. ", colors used: " .. texture:get_colors_used())

last_time = os.time()
deltatime = 0
frames = 0

function randomFloat(min, max)
    return min + math.random() * (max - min)
end

function update()
    frames = frames + 1

    if window:is_key_down("space") then
        renderer:set_background_color(Color.new(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1), 1))
    end

    if window:is_key_down("left_control") and window:is_key_down("c") then
        print("woo")
    end

    if window:is_key_down("left_control") and window:is_key_down("v") then
        print("Clipboard contains: \"" .. window:get_clipboard() .. "\"")
    end

    if os.difftime(os.time(), last_time) >= 1 then
        window:set_title(title .. " || time: " .. os.difftime(os.time(), start_time) .. " || ms/frame: " .. 1000/frames)
        frames = 0
        last_time = last_time + 1;
    end
end

function render()
    if window:is_key_down("escape") then
        window:close()
    end

    if window:is_focused() then
        renderer:render()
    end

    window:swap_buffers()
end

while window:is_open() do
    update()
    render()
end
