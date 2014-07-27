device = Device.new()

window = device:get_window()
window:open(800, 600, "bajs")

renderer = device:get_renderer()
gui_mgr = device:get_gui_manager()
content_mgr = device:get_content_manager()

last_time = os.time()
frames = 0
frametime = 0

renderer:initialize()

texture = content_mgr:get_texture2d("data/textures/error.png", false)

img = gui_mgr:get_image()
img:set_texture(texture)

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
        window:set_title("ms/frame: " .. frametime)
        frames = 0
        last_time = os.time()
    end

    renderer:draw()
    gui_mgr:render()
    window:swap_buffers()
end
