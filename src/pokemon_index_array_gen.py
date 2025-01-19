# these are the ranges of valid pokemon indices. the gaps indicate values not preseent in the pokemon index array.
# don't ask me what the pokemon index array is for, i dont know yet.
valid_ranges = [
    [000, 200],
    [228, 377],
    [381, 415],
    [419, 444],
    [447, 447],
    [450, 457],
    [459, 459],
    [461, 461],
    [463, 518],
    [524, 531],
    [533, 537],
    [539, 539],
    [557, 557],
    [559, 559],
]

pokemon_index_array = [
    num 
    for (start, end) in valid_ranges 
    for num in range(start, end + 1)
]

header_csv = ','.join([f"{x}" for x in pokemon_index_array])

with open("build/WPSE01_01/include/pokemon_index_array.csv", "w") as f:
    f.write(header_csv)
