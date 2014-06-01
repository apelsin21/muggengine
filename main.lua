start_time = os.clock()

window = Window.new(800, 600, "Lua test")

input = InputHandler.new()

while window:is_open() == true do
    if input:is_key_down("Escape") == true then
        window:close()
    end
end

end_time = os.clock() - start_time

print("Ran for " .. end_time .. " seconds.")
