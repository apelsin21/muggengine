engine = Engine.new()

window = engine:get_window()
renderer = engine:get_renderer()
content_mgr = engine:get_content_manager()
gui_mgr = engine:get_gui_manager()
net_mgr = engine:get_net_manager()

renderer:initialize()

texture = content_mgr:create_texture2d("data/textures/ball.png", false)
texture:set_filter("Linear", "Linear")

ball = gui_mgr:create_sprite()
ball:set_position(Vector2D.new(0.5, -0.5))
ball:set_scale(Vector2D.new(0.5, 0.5))
ball:set_rotation(3.14)

batch = gui_mgr:create_spritebatch()
batch:add_sprite(ball)
batch:set_texture(texture)

lastkey = ""

mouse = Mouse.new()
keyboard = Keyboard.new()

function update()
    if keyboard:is_key_down("Escape") and lastkey ~= "Escape" then
        window:close()
        lastkey = "Escape"
    elseif keyboard:is_key_down("Space") then
        renderer:set_background_color(Color.new(math.random(0.0, 1.0), math.random(0.0, 1.0), math.random(0.0, 1.0), 1))
    elseif keyboard:is_key_down("F11") and lastkey ~= "F11" then
        if not window:is_fullscreen() then
            window:set_borderless_fullscreen()
        else
            window:set_windowed()
        end

        lastkey = "F11"
    elseif keyboard:is_key_down("F3") and lastkey ~= "F3" then
        if window:is_cursor_hidden() then
            window:show_cursor()
        else
            window:hide_cursor()
        end

        lastkey = "F3"
    elseif keyboard:is_key_down("F1") and lastkey ~= "F1" then
        renderer:set_wireframe(not renderer:get_wireframe())
        lastkey = "F1"
    elseif keyboard:is_key_down("Return") and lastkey ~= "Return" then
        client:connect("127.0.0.1", 2300, 3000);
        lastkey = "Return"
    elseif lastkey ~= "" and keyboard:is_key_up(lastkey) then
        lastkey = ""
    end 

    window:set_title("ms/frame: " .. renderer:get_frametime())
end

while window:is_open() do
    update()

    engine:render()
    batch:render()
end
