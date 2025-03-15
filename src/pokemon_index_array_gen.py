# TODO(KooShnoo): document. rename. cleanup. this file actually generates an array mapping dexnumbers 
# to indices into the array of PiiProp (pokemon properties). the gaps represent pokemon with alternate forms,
# who have separete PiiProp properties for each form.
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
