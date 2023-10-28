# Generate the temp.h file 
$(info Generating files... $(shell python3 gen.py translations/$(MLT_LANG) > temp.h))

MODULE_CFLAGS := -DSTANDALONE

ifdef MCUFONT
MODULE_CFLAGS += -DMCUFONT
endif

MODULE_CFLAGS += -D 'FONT_NAME="fixed_10x20"'

#$(info Formatting... $(shell clang-format -style=file -i mlt.c mcu.c))

# Compile with mcufont
ifdef MCUFONT
MCUFONT_C=$(shell ls mcufont/decoder/*.c | sed 's/\.c/\.o/g') mcu.o
MODULE_CFLAGS+=-Imcufont/fonts/ -Imcufont/decoder/
endif

MODULE_NAME=mlt
MODULE_OBJS=mlt.o $(MCUFONT_C)
include ../../modules/Makefile.modules
