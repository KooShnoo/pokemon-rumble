"""
simple hacky script to copy symbols from a handcrafted json file to symbols.txt.
customize to your liking.
it's useful for batch-editing symbols, or importing them from the crummy map files ghidra poops out.

lmk if you know a better way of importing symbols from ghdira into symbols.txt (KooShnoo) and document it please
"""


import json

with open("./config/WPSE01_01/symbols.txt") as f:
    symbols = f.readlines()
    
symbol_dict = {}

dups=0
for i, line in enumerate(symbols):
    tokens = line.split()
    
    symbol_name = tokens[0]
    addr = tokens[2].split(':')[-1][:-1]
    
    if symbol_name in symbol_dict:
        print(f"!!WARNING!! Duplicate symbol `{symbol_name}` found originally at {symbol_dict[symbol_name]}, then again at {addr}")
        dups += 1

    symbol_dict[symbol_name] = addr
    
if dups > 0:
    print(f"symbols.txt contains {dups} duplicate symbols. these will cause linker errors, remove duplicates.")
    exit(1)
else:
    print(f"no duplicates detected, all OK! :)")
    
