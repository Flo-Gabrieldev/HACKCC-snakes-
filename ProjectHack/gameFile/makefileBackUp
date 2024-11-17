# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++17 -I./include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lcurl

# Directories and Executable
SRC = main.cpp
EXEC = gamePro

# Default target to compile and run
all: $(EXEC)
	./$(EXEC)

# Compile the source into an executable
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(EXEC)

run:
	./$(EXEC)
