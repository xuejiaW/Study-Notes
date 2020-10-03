CC		:= g++
CFLAGS	:= -std=c++17 -Wall -Wextra -g

BIN		:= ../..//bin

LIBRARIES	:= -lglad -lglfw3dll # Add Lib file

EXECUTABLE	:= main.exe
SOURCEDIRS	:= ./
INCLUDEDIRS	:= ../../include
LIBDIRS		:= ../../lib

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS))

SOURCES		:= $(wildcard  $(SOURCEDIRS)*.cpp)


$(BIN)/$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)

all: clean run

run: $(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)

test:
	@echo $(wildcard  $(SOURCEDIRS)*.cpp)