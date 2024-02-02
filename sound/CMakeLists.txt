# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DSP_Learning VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)


# global varialbes
set(DIR "src")
# Add the executable target

add_executable(phasor ${DIR}/phasor.c)
add_executable(sine ${DIR}/sine.c)
add_executable(saw ${DIR}/saw.c)
add_executable(mouse ${DIR}/mouse.c)



#find_package(PkgConfig)
find_package(raylib REQUIRED)
find_library(JACK_LIBRARY jack)

# Include directories for header files
target_include_directories(mouse
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# linking mouse
target_link_libraries(mouse PRIVATE raylib)
target_link_libraries(mouse PRIVATE jack)

#linking others
target_link_libraries(phasor PRIVATE jack)
target_link_libraries(sine PRIVATE jack m)
target_link_libraries(saw PRIVATE jack)




# Optional: Add compiler flags
add_compile_options(-Wall -Wextra -lm -g)
set(COMPILE_FLAGS "${COMPILE_FLAGS} -Wall -Wextra -lm -g")
