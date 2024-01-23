# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(AttractorSonification VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Add the executable target
add_executable(AttractorSoundExecutable
    src/main.c  # Assuming main.c is in the src directory
)

# Include directories for header files
target_include_directories(AttractorSoundExecutable
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)


#find_package(PkgConfig)

# Optional: Add additional libraries
find_package(raylib REQUIRED)
target_link_libraries(AttractorSoundExecutable PRIVATE raylib)

# Find jack libraries and include directories
find_library(JACK_LIBRARY jack)
target_link_libraries(AttractorSoundExecutable PRIVATE jack)



# Optional: Add compiler flags
# target_compile_options(AttractorSoundExecutable PRIVATE -Wall -Wextra)
target_compile_options(AttractorSoundExecutable PRIVATE -Wall -Wextra)
