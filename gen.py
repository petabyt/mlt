import sys

f = open(sys.argv[1], "r")
contents = f.read()
print("const char current_translation[" + str(len(contents)) + "] = {")
for i in contents:
    print(str(ord(i)) + ",")
print("};")
