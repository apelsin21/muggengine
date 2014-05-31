start_time = os.clock()

window = Window.new(800, 600, "Lua test")

window:set_position(784, 95)

print("Window position: " .. window:get_position_x() .. "x" .. window:get_position_y())


print("Window resolution: " .. window:get_resolution_x() .. "x" .. window:get_resolution_y())

window:set_fullscreen(true)

print("Is window fullscreen?")
if window:get_fullscreen() == true then
    print("yes")
else
    print("no")
end

input = InputHandler.new()

end_time = os.clock() - start_time

print("Time: " .. end_time)
