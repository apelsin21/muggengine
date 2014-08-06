device = Device.new()

window = device:create_window()
title = "MuggEngine Window"
window:open(800, 600, title)

renderer = device:create_renderer()
content_mgr = device:create_content_manager()
gui_mgr = device:create_gui_manager()
scene_mgr = device:create_scene_manager()

renderer:initialize()

keyboard = Keyboard.new()

img = gui_mgr:create_image()
img:set_texture(content_mgr:create_texture2d("data/textures/error.png", false))

node = scene_mgr:create_node()

mesh = content_mgr:create_mesh("data/models/astronaut1.3ds")

node:add_mesh(mesh)

print("Mesh has " .. mesh:get_number_of_vertices() .. " vertices")
print("Mesh has " .. mesh:get_number_of_indices() .. " indices")
print("Mesh has " .. mesh:get_number_of_uvs() .. " texture coordinates")
print("Mesh has " .. mesh:get_number_of_normals() .. " normals")

lastkey = ""

while window:is_open() do
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

    window:set_title(title .. " ms/frame: " .. renderer:get_frametime())

    device:render()
end
