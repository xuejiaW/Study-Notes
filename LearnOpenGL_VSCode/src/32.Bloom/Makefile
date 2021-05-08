CC		:= g++
CFLAGS	:= -std=c++17 -Wall -Wextra -g -w

BIN		:= ../../bin

LIBRARIES	:= -lglad -lglfw3dll -lassimp # Add Lib file

EXECUTABLE	:= main.exe
INCLUDEDIRS	:= ../../include
LIBDIRS		:= ../../lib
SOURCEDIRS	:= ./

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS))

SOURCES := $(addsuffix *.cpp, $(shell ls -d ../Framework/*/)) # Get the source files from sub folders of the ../Framework/
SOURCES += ../Framework/*.cpp
SOURCES += $(SOURCEDIRS)*.cpp

SOURCES		:= $(wildcard  $(SOURCES))
OBJECTS		:= $(SOURCES:.cpp=.o)
DEPENDENCIES := $(SOURCES:.cpp=.d)

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)

%.o : %.cpp$<
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) -c $< -o $@ $(LIBRARIES) 

%.d : %.cpp
	@set -e; \
	$(CC) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPENDENCIES)

all: clean run

build: $(BIN)/$(EXECUTABLE)

run: $(BIN)/$(EXECUTABLE)
	$(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)
	-$(RM) $(DEPENDENCIES)

.PHONY: test
test:
	@echo $(SOURCES)