cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MySFMLGame LANGUAGES CXX)

# Add the SFML include directory
include_directories(C:/Users/kphon/Downloads/SFML-2.6.2-windows-vc17-64-bit/SFML-2.6.2/include)

# Add the executable
add_executable(my_game main.cpp)

# Link SFML libraries
target_link_directories(my_game PRIVATE C:/Users/kphon/Downloads/SFML-2.6.2-windows-vc17-64-bit/SFML-2.6.2/lib)
target_link_libraries(my_game sfml-graphics sfml-window sfml-system)
