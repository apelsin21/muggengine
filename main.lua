engine = Engine.new()

window = engine:get_window()
renderer = engine:get_renderer()
content_mgr = engine:get_content_manager()
gui_mgr = engine:get_gui_manager()
net_mgr = engine:get_net_manager()

renderer:initialize()

ball_array = {}
num_balls = 20000
balltexture = content_mgr:create_texture2d("data/textures/ball.png", false)
ballscale = Vector2D.new(0.1, 0.1)
ballpos = Vector2D.new(1.0, 0.0)

for i = 1, num_balls do
    ball_array[i] = gui_mgr:create_image()
    ball_array[i]:set_texture(balltexture)
    ball_array[i]:set_scale(ballscale)
end

lastkey = ""

mouse = Mouse.new()
keyboard = Keyboard.new()

start_time = os.clock()

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

    deltatime = os.clock() - start_time
    start_time = os.clock()

    pos = ball_array[1]:get_position()

    if keyboard:is_key_down("W") then
        pos:set_y(pos:get_y() + 0.1 * deltatime)
    end
    if keyboard:is_key_down("S") then
        pos:set_y(pos:get_y() - 0.1 * deltatime)
    end
    if keyboard:is_key_down("A") then
        pos:set_x(pos:get_x() - 0.1 * deltatime)
    end
    if keyboard:is_key_down("D") then
        pos:set_x(pos:get_x() + 0.1 * deltatime)
    end

    ball_array[1]:set_position(Vector2D.new(0.1, 0.5))
end

while window:is_open() do
    update()

    engine:render()
end
