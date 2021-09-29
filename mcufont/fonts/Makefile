# Path to the command-line utility program
MCUFONT = ../encoder/mcufont

# Names of fonts to process
FONTS = fixed_10x20

# Characters to include in the fonts
CHARS = 0-255 0x2010-0x2015

all: $(FONTS:=.c) $(FONTS:=.dat) fonts.h

clean:
	rm -f $(FONTS:=.c) $(FONTS:=.dat)

fonts.h: $(FONTS:=.c)
	/bin/echo -e $(foreach font,$(FONTS),'\n#include "'$(font)'.c"') > $@

%.c: %.dat $(MCUFONT)
	$(MCUFONT) rlefont_export $<

%.dat: %.bdf
	$(MCUFONT) import_bdf $<
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 10
