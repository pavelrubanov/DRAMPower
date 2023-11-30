CC := g++
CFLAGS := -g -I. -I..

# Compile all C++ source files in the current directory
SOURCES := $(wildcard *.cc)
OBJECTS := $(SOURCES:.cc=.o)

# Compile all C++ source files in the 'libdrampower' directory
LIB_SOURCES := $(wildcard libdrampower/*.cc)
LIB_OBJECTS := $(LIB_SOURCES:.cc=.o)

# Target for the final library
LIBRARY := libdrampower.a

all: $(LIBRARY)

# Compile rule for C++ source files in the current directory
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Compile rule for C++ source files in the 'libdrampower' directory
libdrampower/%.o: libdrampower/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Archive all object files into the library
$(LIBRARY): $(OBJECTS) $(LIB_OBJECTS)
	ar src $@ $^

clean:
	rm -f $(OBJECTS) $(LIB_OBJECTS) $(LIBRARY)
