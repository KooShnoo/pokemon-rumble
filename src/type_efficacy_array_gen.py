from enum import Enum
import json;
import os

types = ["NORMAL", "FIGHTING", "FLYING", "POISON", "GROUND", "ROCK", "BUG", "GHOST", "STEEL", "???", "FIRE", "WATER", "GRASS", "ELECTRIC", "PSYCHIC", "ICE", "DRAGON", "DARK"]

data = "03 03 03 03 03 02 03 00 02 03 03 03 03 03 03 03 03 03 04 03 02 02 03 04 02 00 04 03 03 03 03 03 02 04 03 04 03 04 03 03 03 02 04 03 02 03 03 03 04 02 03 03 03 03 03 03 03 02 02 02 03 02 00 03 03 03 04 03 03 03 03 03 03 03 00 04 03 04 02 03 04 03 04 03 02 04 03 03 03 03 03 02 04 03 02 03 04 03 02 03 04 03 03 03 03 04 03 03 03 02 02 02 03 03 03 02 02 03 02 03 04 03 04 03 03 04 00 03 03 03 03 03 03 04 02 03 03 03 03 03 04 03 03 02 03 03 03 03 03 04 03 03 02 03 02 02 03 02 03 04 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 02 04 03 04 03 02 02 04 03 03 04 02 03 03 03 03 03 04 04 03 03 03 03 04 02 02 03 03 03 02 03 03 03 02 02 04 04 02 03 02 03 02 04 02 03 03 03 02 03 03 03 04 03 00 03 03 03 03 03 03 04 02 02 03 03 02 03 03 04 03 04 03 03 03 03 02 03 03 03 03 03 02 03 03 00 03 03 04 03 04 03 03 03 02 03 02 02 04 03 03 02 04 03 03 03 03 03 03 03 03 03 02 03 03 03 03 03 03 03 04 03 03 02 03 03 03 03 03 04 02 03 03 03 03 03 04 03 03 02".split()

EFFICACY_MAP = {
    "NO_EFFECT": 0,
    "UNUSED": 1,
    "NOT_VERY_EFFECTIVE": 2,
    "EFFECTIVE": 3,
    "SUPER_EFFECTIVE": 4,
}

with open("src/type_chart.json") as f: 
    table = json.load(f)

flat = []

for atk in types:
    for defend in types:
        value = table[atk][defend]
        flat.append(EFFICACY_MAP[value])

os.makedirs("build/WPSE01_01/include", exist_ok=True)
with open("build/WPSE01_01/include/typeChart.inc", "w+") as f:
    for i, v in enumerate(flat):
        f.write(f"{v}, // {types[i // 18]} -> {types[i % 18]}\n")