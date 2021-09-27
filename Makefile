# Specify LANG for standalone 
# make install_qemu MLT_LANG=es


_A:=$(shell python3 gen.py translations/$(MLT_LANG) > temp.h)
MODULE_CFLAGS := -DSTANDALONE -DMLT_LANG=$(MLT_LANG)

_B := $(shell astyle --style=allman mlt.c; rm -rf *.orig)

# Compile with mcufont
MCUFONT=$(shell ls mcufont/decoder/*.c | sed 's/\.c/\.o/g') mcu.o
MODULE_CFLAGS+=-Imcufont/fonts/ -Imcufont/decoder/

MODULE_NAME=mlt
MODULE_OBJS=mlt.o $(MCUFONT)
include ../../modules/Makefile.modules
