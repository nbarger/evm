# a simple script that writes some binary values

code = []
i = 0

while True:
    try:
        h = int(input("Enter a hex value (press enter to quit)[{}]: ".format(i)), 16)
        i += 1
    except: h = None
    if h == None: break
    code.append(h)

print("Writing data...")
with open("../test.bin", "wb") as f:
    f.write(bytes(code))

print("Done")
