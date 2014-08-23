engine = Engine.new()

window = engine:get_window()
renderer = engine:get_renderer()
content_mgr = engine:get_content_manager()
gui_mgr = engine:get_gui_manager()
net_mgr = engine:get_net_manager()

renderer:initialize()

-- scene_mgr = engine:get_scene_manager()
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

server = net_mgr:create_server()
server:initialize(2300)

client = net_mgr:create_client()
client:initialize()

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

    if server:get_latest_event() == "Connected" then
        print("Connected to " .. server:get_latest_event_address())
    elseif server:get_latest_event() == "Disconnected" then
        print("Disconnected from " .. server:get_latest_event_address())
    elseif server:get_latest_event() == "Received" then
        print("Received " .. server:get_latest_event_data() .. " from " .. server:get_latest_event_addres())
    end
    
    server:clear_latest_event()

    if client:get_latest_event() == "Connected" then
        print("Connected to " .. client:get_peer_address())
    elseif client:get_latest_event() == "Disconnected" then
        print("Disconnected from " .. server:get_peer_address())
    elseif client:get_latest_event() == "Received" then
        print("Received from " .. server:get_peer_address())
    end

    client:clear_latest_event()
end

while window:is_open() do
    update()

    engine:render()
end
