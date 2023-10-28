# Magic Lantern Translator
A PoC Magic Lantern module that implements localization in the menus.

![demo](demo.jpg)

The `bmp_printf` function is hijacked in order to print translated strings.
In order to get menu text items, I logged `bmp_printf` input into a file, removed duplicates, and manually removed generated strings.

## Usage
Drop `mlt.mo` in `ML/modules`.

## Compiling
```
make
```

You can compile with the following flags:
- `MCUFONT=X`: Compile with the [mcufont](https://github.com/mcufont/mcufont) rendering backend.  

## TODO/Help Needed:
- [ ] Manually review translations, and add more translations
- [ ] Case insensitive string searching

# Credits
https://github.com/mcufont/mcufont (MIT License)  
(https://github.com/fcambus/spleen) Uses "spleen" 12x24 BDF font, (BSD 2-Clause "Simplified" License)  
