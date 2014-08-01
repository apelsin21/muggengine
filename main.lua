device = Device.new()

window = device:create_window()
window:open(800, 600, "bajs")

renderer = device:create_renderer()
content_mgr = device:create_content_manager()
gui_mgr = device:create_gui_manager()

renderer:initialize()

keyboard = Keyboard.new()

img = gui_mgr:get_image()
img:set_texture(content_mgr:get_texture2d("data/textures/error.png", false))

while window:is_open() do
    if keyboard:is_key_down("ESCAPE") then
        window:close()
    end

    window:set_title("ms/frame: " .. renderer:get_frametime())

    renderer:draw()
    gui_mgr:render()
    window:swap_buffers()
end
