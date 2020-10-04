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

SOURCES		:= $(wildcard  $(SOURCEDIRS)*.cpp ../Framework/*.cpp ../Framework/Components/*.cpp ../Framework/GameObjects/*.cpp ../Framework/Mesh/*.cpp ../Framework/Shaders/*.cpp)


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
	@echo $(SOURCES)