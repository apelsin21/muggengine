local input

print("Enter name of script you want to run, \"quit\" exits the program.")
input = io.read()

if input == "quit" then
else
    dofile("data/scripts/" .. input .. ".lua")
end
