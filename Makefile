#Makefile for repository

APP=repository

DEBUG=yes
SRC=src
BIN=bin
INCLUDE=include
LIBS=-l cunit -l pthread

CFLAGS=-Wall -pedantic -std=c99 -D_DEFAULT_SOURCE

ifeq ($(DEBUG),yes)
CFLAGS+=-g
endif



clean:
		$(RM) -r $(BIN)

all: clean $(BIN)/$(APP)

test: clean $(BIN)/$(APP)
		$(BIN)/$(APP)
		
.PHONY: clean all

		
				