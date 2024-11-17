# Detect the architecture
ARCH = $(shell uname -m)

# Compiler and linker settings
ifeq ($(ARCH), x86_64)  # Intel (x86_64)
    CXX = clang++  # Use clang++ for Intel Macs
    CXXFLAGS = -std=c++17 -I./include -arch x86_64  # Intel architecture
else  # Apple Silicon (M1/M2, arm64)
    CXX = clang++  # Use clang++ for Apple Silicon Macs
    CXXFLAGS = -std=c++17 -I./include -arch arm64  # ARM architecture (M1/M2)
endif

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lcurl  # Linker flags for libraries

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

# Run the executable
run:
	./$(EXEC)

