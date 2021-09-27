# Magic Lantern Translation
A Magic Lantern module that hijacks the `bmp_puts` function  
and "translates" the output.

![demo](demo.jpg)

## Usage
Drop `mlt.mo` in `ML/modules`.

In order to get menu text items, I logged bmp_printf  
input into a file and removed duplicates and generated  
strings.  

## Help Needed:
- [ ] Manually review translations, and add more translations
- [ ] Case insensitive string searching (possibly ignore symbols too)
- [ ] "Translate" parts of a string, ignoring generated parts

## How's Speed?
Of course, running `strcmp` 100+ times every time the menu is drawn sounds  
very CPU intensive. From my experience, it has no noticible effect. It  
feels just as snappy without it enabled. As for battery life, I'm not 100% sure.  
