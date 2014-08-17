device = Device.new()

window = device:create_window()
title = "MuggEngine Window"
window:open(800, 600, title)

renderer = device:create_renderer()
content_mgr = device:create_content_manager()
gui_mgr = device:create_gui_manager()

renderer:initialize()

keyboard = Keyboard.new()

-- scene_mgr = device:create_scene_manager()
-- shaderprogram = content_mgr:create_shaderprogram()
-- shaderprogram:add(content_mgr:create_shader("VertexShader", "data/shaders/scene_vertex.glsl"))
-- shaderprogram:add(content_mgr:create_shader("FragmentShader", "data/shaders/scene_fragment.glsl"))
-- shaderprogram:link()
-- scene_mgr:set_shaderprogram(shaderprogram)
-- node = scene_mgr:create_node()
-- mesh = content_mgr:create_mesh("data/models/media/dwarf.x")
-- node:add_mesh(mesh)
-- print("Mesh filepath " .. mesh:get_filepath())
-- print("Mesh has " .. mesh:get_number_of_vertices() .. " vertices")
-- print("Mesh has " .. mesh:get_number_of_indices() .. " indices")
-- print("Mesh has " .. mesh:get_number_of_uvs() .. " texture coordinates")
-- print("Mesh has " .. mesh:get_number_of_normals() .. " normals")

img = gui_mgr:create_image()
img:set_texture(content_mgr:create_texture2d("data/textures/error.png", false))

scale = Vector2D.new()
scale:set_xy(0.1, 0.1)
img:set_scale(scale)

img2 = gui_mgr:create_image()
img2:set_texture(content_mgr:create_texture2d("data/models/media/dwarf.jpg", false))
img2:get_texture():set_filter("Linear", "Linear")

lastkey = ""

mouse = Mouse.new()

position = Vector2D.new()

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
    elseif lastkey ~= "" and keyboard:is_key_up(lastkey) then
        lastkey = ""
    end 
    
    if keyboard:is_key_down("W") and position:get_y() <= 1 then
        position:set_y(position:get_y() + 0.1)
    end
    if keyboard:is_key_down("S") and position:get_y() >= -1 then
        position:set_y(position:get_y() - 0.1)
    end
    if keyboard:is_key_down("A") and position:get_x() >= -1 then
        position:set_x(position:get_x() - 0.1)
    end
    if keyboard:is_key_down("D") and position:get_x() <= 1 then
        position:set_x(position:get_x() + 0.1)
    end

    img:set_position(position)

    if mouse:is_left_button_down() or mouse:is_right_button_down() or mouse:is_middle_button_down() then
        print("Mouse: " .. mouse:get_x() .. "x" .. mouse:get_y())
    end

    window:set_title(title .. " ms/frame: " .. renderer:get_frametime())
end

while window:is_open() do
    update()

    device:render()
end
