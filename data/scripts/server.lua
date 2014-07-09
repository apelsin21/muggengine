server = Server.new()
server:initialize(2300)

while true do
    server:poll(0)
end
