#########################################################
#
# project name : SDL_initiation
# date : 01-17-2016
# author : aymen.laouini@ymail.com
#
# %.o : it is the relative object file of a source file
# %.c : it is the relative source file of an object file
# $@  : it is what we find on the left of the colomn ":"
# $^  : it is what we find on the right of the colomn ":"
# $<  : it is the first item in the dependencies list
#
#########################################################
IDIR=./include
CC=gcc
EXEC=../PCEXE

CFLAGS=-I$(IDIR)
SFLAGS=

ODIR=../obj
LIBS=-lpthread

SRCS =  $(OBJ:.o=.c)
SRCDIRS = ./src

HEADIRS = ./include

_DEPS = generator.h project_def.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o generator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS) $(LIBS)

$(EXEC): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(SFLAGS) $(LIBS)
	chmod +x $(EXEC)

.PHONY: clean

# If makefile changes, maybe the list of sources has changed, so update doxygens list
PCEXE: Doxyfile
		echo INPUT         =  $(SRCDIRS) >> Doxyfile
		echo FILE_PATTERNS =  $(HEADIRS) $(SRCS) >> Doxyfile

doxy: PCEXE $(SRCS)
		doxygen Doxyfile

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
mrproper: clean
	rm -rf $(EXEC)
