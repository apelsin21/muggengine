local input

repeat
    print("Do you want to be client or server? \"quit\" exits the program.")
    input = io.read()

    if input == "client" then
        dofile("data/scripts/client.lua")
    end
    if input == "server" then
        dofile("data/scripts/server.lua")
    end
until input == "client" or input == "server" or input == "quit"
