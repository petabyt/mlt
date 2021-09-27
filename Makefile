# Specify LANG for standalone 
# make install_qemu MLT_LANG=es

ifdef MLT_LANG
$(info MLT is being compiled as standalone with translations/mlt_$(MLT_LANG))
_A:=$(shell python3 gen.py translations/mlt_$(MLT_LANG) > temp.h)
MODULE_CFLAGS := -DSTANDALONE -DMLT_LANG=mlt_$(MLT_LANG)
endif

_B := $(shell astyle --style=allman mlt.c; rm -rf *.orig)

# Compile with mcufont
MCUFONT=$(shell ls mcufont/decoder/*.c | sed 's/\.c/\.o/g') mcu.o
MODULE_CFLAGS+=-Imcufont/fonts/ -Imcufont/decoder/

MODULE_NAME=mlt
MODULE_OBJS=mlt.o $(MCUFONT)
include ../../modules/Makefile.modules
