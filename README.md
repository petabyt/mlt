# Magic Lantern Translation
A Magic Lantern module that hijacks the `bmp_puts` function  
and "translates" the output.

![demo](demo.jpg)

In order to create a translation, follow the format of  
`translation/mlt_es`.  

In order to get menu text items, I logged bmp_printf  
input into a file and removed duplicates and generated  
strings.  

# TODO:
- [x] Hijack the `bmp_printf` function from a module, not from source code.
- [ ] Use a decent format, not `|` and `\n`.
- [ ] Case insensitive string searching (possibly ignore symbols too)

# How's Speed?
Of course, running `strcmp` 100+ times every time the menu is drawn sounds  
very CPU intensive. From my experience, it has no noticible effect. It  
feels just as snappy without it enabled. As for battery life, I'm not 100% sure.  
