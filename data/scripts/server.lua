server = Server.new()
server:initialize(2300)

while true do
    if server:get_latest_event() == "Disconnected" then
        print(server:get_latest_event_address() .. " disconnected!")
    elseif server:get_latest_event() == "Connected" then
        print(server:get_latest_event_address() .. " connected!")
    elseif server:get_latest_event() == "Received" then
        print(server:get_latest_event_address() .. " sent: " .. server:get_latest_event_data())
    end
    
    server:poll(0)
end
