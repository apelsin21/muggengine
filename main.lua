engine = Engine.new()

window = engine:get_window()

renderer = engine:get_renderer()
content_mgr = engine:get_content_manager()
gui_mgr = engine:get_gui_manager()
net_mgr = engine:get_net_manager()

renderer:initialize()

texture = content_mgr:create_texture2d("data/textures/error.png", false)
texture:set_filter("Nearest", "Nearest")

lastkey = ""

tiles = {}
tiles.width = (window:get_width() / (texture:get_width() * 3))
tiles.height = (window:get_height() / (texture:get_height() * 3))

function tiles.count(self)
    return self.width*self.height
end

velocity = Vector2D.new(0.03, 0.01)
scale = Vector2D.new(1 / tiles.width, 1 / tiles.height)
position = Vector2D.new(-1, -1)

for x = 0, tiles.width do
    tiles[x] = {}
    
    if x ~= 0 then
        position:set_x(position:get_x() + scale:get_x()*2)
    end

    for y = 0, tiles.height do
        tiles[x][y] = gui_mgr:create_sprite()
        if y ~= 0 then
            position:set_y(position:get_y() + scale:get_y()*2)
        end

        tiles[x][y]:set_scale(scale)
        tiles[x][y]:set_position(position)
    end

    position:set_y(-1)
end

print("There are " .. tiles:count() .. " tiles in total")
print(tiles.width .. " horizontally, " .. tiles.height .. " vertically")

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
end
