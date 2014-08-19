engine = Engine.new()

window = engine:get_window()
renderer = engine:get_renderer()
content_mgr = engine:get_content_manager()
gui_mgr = engine:get_gui_manager()

renderer:initialize()

-- scene_mgr = engine:create_scene_manager()
-- shaderprogram = content_mgr:create_shaderprogram()
-- shaderprogram:add(content_mgr:create_shader("VertexShader", "data/shaders/scene_vertex.glsl"))
-- shaderprogram:add(content_mgr:create_shader("FragmentShader", "data/shaders/scene_fragment.glsl"))
-- shaderprogram:link()
-- scene_mgr:set_shaderprogram(shaderprogram)
-- node = scene_mgr:create_node()
-- mesh = content_mgr:create_mesh("data/models/complexshape.nff")
-- node:add_mesh(mesh)
-- print("Mesh filepath " .. mesh:get_filepath())
-- print("Mesh has " .. mesh:get_number_of_vertices() .. " vertices")
-- print("Mesh has " .. mesh:get_number_of_indices() .. " indices")
-- print("Mesh has " .. mesh:get_number_of_uvs() .. " texture coordinates")
-- print("Mesh has " .. mesh:get_number_of_normals() .. " normals")

img_array = {}
num_images = 10

ball_texture = content_mgr:create_texture2d("data/textures/ball.png", false)
ball_pos = Vector2D.new()

for i = 0, num_images do
    img_array[i] = gui_mgr:create_image()
    img_array[i]:set_texture(ball_texture)
    ball_scale = Vector2D.new()
    scale = 0.1
    ball_scale:set_xy(scale, scale)
    img_array[i]:set_scale(ball_scale)
    ball_pos:set_xy(math.random() * 1.0 + -1.0, math.random() * 0.8 + 0.1)
    img_array[i]:set_position(ball_pos)
end

lastkey = ""

mouse = Mouse.new()
keyboard = Keyboard.new()

change_array = {}

for i = 0, num_images do
    change_array[i] = Vector2D.new()
    change_array[i]:set_xy(math.random() * 0.5 + -0.5, math.random() * 0.5 + -0.5)
end

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

    for i = 0, num_images do
        img_array[i]:set_rotation(img_array[i]:get_rotation() + 0.1)
 
        if img_array[i]:get_rotation() >= 3.14*2 then
            img_array[i]:set_rotation(0)
        end

        img_array[i]:set_position(img_array[i]:get_position() + change_array[i])

        if img_array[i]:get_position():get_x() >= 1 then
            change_array[i]:set_x(change_array[i]:get_x() * -1)
        end
        if img_array[i]:get_position():get_x() <= -1 then
            change_array[i]:set_x(change_array[i]:get_x() * -1)
        end
        if img_array[i]:get_position():get_y() >= 1 then
            change_array[i]:set_y(change_array[i]:get_y() * -1)
        end
        if img_array[i]:get_position():get_y() <= -1 then
            change_array[i]:set_y(change_array[i]:get_y() * -1)
        end
 
    end

    window:set_title(" ms/frame: " .. renderer:get_frametime())
end

while window:is_open() do
    update()

    engine:render()
end
