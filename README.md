# Magic Lantern Translation
A Magic Lantern module that hijacks the `bmp_puts` function  
and "translates" the output.

![demo](demo.png)

In order to create a translation, follow the format of  
`translation/mlt_es`. In order to get menu text items, I  
logged bmp_printf input into a file and removed duplicates  
and generated strings.  

# TODO:
- [x] Hijack the `bmp_printf` function from a module, not from source code.
- [ ] Use XML, not `|` and `\n`.
- [ ] Case insensitive string searching