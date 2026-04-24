# this file generates an array mapping pokedex numbers to indices into the array of all PiiProp (pokemon properties).
# this is necessary to account for the extra PiiProp entries for alternate pokemon forms.

POKEDEX_LENGTH = 496

# Maps a dex number to the number of alternate forms (for pokemon with multiple forms).
alternate_form_counts = {
    201:27, # Unown
    351:3,  # Castform
    386:3,  # Deoxys
    412:2,  # Burmy
    413:2,  # Wormadam
    421:1,  # Cherrim
    422:1,  # Shellos
    423:1,  # Gastrodon
    492:1,  # Shaymin
    479:5,  # Rotom
    487:1,  # Giratina
    493:17, # Arceus
    494:1,  # Egg
}

pokemon_index_array = [0]
skipped_forms = 0
for dex_index in range(0, POKEDEX_LENGTH - 1):
    pokemon_index_array.append(dex_index + skipped_forms)
    
    dex_no = dex_index + 1
    alternate_form_count = alternate_form_counts.get(dex_no) or 0
    skipped_forms += alternate_form_count

header_csv = ','.join([f"{x}" for x in pokemon_index_array])

with open("build/WPSE01_01/include/pprNo.csv", "w+") as f:
    f.write(header_csv)
    
