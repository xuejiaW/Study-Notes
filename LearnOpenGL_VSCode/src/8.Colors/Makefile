CC		:= g++
CFLAGS	:= -std=c++17 -Wall -Wextra -g -w

BIN		:= ../..//bin

LIBRARIES	:= -lglad -lglfw3dll # Add Lib file

EXECUTABLE	:= main.exe
INCLUDEDIRS	:= ../../include
LIBDIRS		:= ../../lib
SOURCEDIRS	:= ./

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS))


SOURCES := $(SOURCEDIRS)*.cpp
SOURCES += ../Framework/*.cpp
SOURCES += $(addsuffix *.cpp, $(shell ls -d ../Framework/*/)) # Get the source files from sub folders of the ../Framework/

SOURCES		:= $(wildcard  $(SOURCES))


$(BIN)/$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)

all: clean run

run: $(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)

.PHONY: test
test:
	@echo $(SOURCES)