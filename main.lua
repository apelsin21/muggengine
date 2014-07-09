client = Client.new()
client:initialize(2, 0, 0)

while true do
    if client:is_connected() == false then
        client:connect("192.168.1.91", 2300, 5000)
    end

    client:poll(0)
end

client:disconnect(3000)
