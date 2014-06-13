window = Window.new(800, 600, "MuggEngine Window")

input = InputHandler.new()

start_time = os.time()

last_time = os.clock()
frames = 0

while window:is_open() == true do
    if input:is_key_down("Escape") == true and window:is_focused() == true then
        window:close()
    end

    current_time = os.clock()
    frames = frames + 1

    if(current_time-last_time) >= 1 then
        print(1000/frames .. " ms/frame")
        frames = 0
        last_time = current_time
    end

    window:swap_buffers()
end

print("Program ran for " .. os.difftime(os.time(), start_time) .. " seconds.")
