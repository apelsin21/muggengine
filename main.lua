device = Device.new()

window = device:create_window()
window:open(800, 600, "MuggEngine Window")

renderer = device:create_renderer()
content_mgr = device:create_content_manager()
gui_mgr = device:create_gui_manager()

renderer:initialize()

keyboard = Keyboard.new()

img = gui_mgr:get_image()
img:set_texture(content_mgr:get_texture2d("data/textures/error.png", false))

lastkey = ""

while window:is_open() do
    if keyboard:is_key_down("Escape") and lastkey ~= "Escape" then
        window:close()
        lastkey = "Escape"
    elseif keyboard:is_key_down("Space") and lastkey ~= "Space" then
        renderer:set_background_color(Color.new(math.random(0, 1), math.random(0, 1), math.random(0, 1), 1))
        lastkey= "Space"
    elseif keyboard:is_key_down("F11") and lastkey ~= "F11" then
        if not window:is_fullscreen() then
            window:set_borderless_fullscreen()
        else
            window:set_windowed()
        end

        lastkey = "F11"
    end

    if lastkey ~= "" and keyboard:is_key_up(lastkey) then
        lastkey = ""
    end

    window:set_title("ms/frame: " .. renderer:get_frametime())

    renderer:draw()
    gui_mgr:render()
    window:swap_buffers()
end
