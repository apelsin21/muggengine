person_array = {}

num_persons = 100000

old_time = os.clock()

for i = 1, num_persons  do
    person_array[i] = Person.new(math.random(num_persons))
    print("Person number " .. i .. " is " .. person_array[i]:get_age() .. " years old.")
end

print("It took " .. os.clock() - old_time .. " seconds to generate " .. num_persons .. " random numbers and print them to stdout")
