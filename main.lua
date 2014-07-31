device = Device.new()

window = device:get_window()
window:open(800, 600, "bajs")

renderer = device:get_renderer()
content_mgr = device:get_content_manager()
gui_mgr = device:get_gui_manager()

last_time = os.time()
frames = 0
frametime = 0

renderer:initialize()

img = gui_mgr:get_image()
img:set_texture(content_mgr:get_texture2d("data/textures/error.png", false))

while window:is_open() do
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
