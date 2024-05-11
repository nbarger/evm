# a simple script that writes some binary values

import sys

if len(sys.argv) < 2:
    print("Please pass an output file")
    exit(1)

code = []
i = 0

while True:
    print(code)
    try:
        h = int(input("Enter a hex value (press enter to quit)[{}]: ".format(i)), 16)
        i += 1
    except: h = None
    if h == None: break
    code.append(h)

print("Writing data...")
with open(sys.argv[1], "wb") as f:
    f.write(bytes(code))

print("Done")
