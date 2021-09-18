# Specify LANG for standalone 
# make install_qemu LANG=es
ifdef LANG
_A:=$(shell python3 gen.py translations/mlt_$(LANG)> temp.h)
MODULE_CFLAGS := -DSTANDALONE -DMLT_LANG=mlt_$(LANG)
endif

_B := $(shell astyle --style=allman mlt.c; rm *.orig)

MODULE_NAME=mlt
MODULE_OBJS=mlt.o
include ../../modules/Makefile.modules
