import sys

langs = ["ade", "aes", "afr"]
langs_name = ["German", "Spanish", "French"]

# Generate language contents
for i in langs:
    f = open("translations/" + i, "rb")
    contents = f.read()
    print("char mlt_" + i + "[" + str(len(contents) + 1) + "] = {")
    for i in contents:
        print(str((i)) + ",")
    print("0};")

# Generate languages array
print("char *mlt_langs[] = {")
for i in langs:
    print("mlt_" + i + ",")
print("};")

print("char *current_translation;")

# Generate languages name array
print('#define MLT_LANGS ', end = "")
for i in langs_name:
    print('"' + i + '", ', end = "")
print("")

print('#define MLT_NLANGS ' + str(len(langs)))
