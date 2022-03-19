cmake_minimum_required (VERSION 3.8)

# Project orbitalsim
project(orbitalsim)

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.1.0
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# From "Working with CMake" documentation:
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_STANDARD 11)
    # AddressSanitizer (ASan)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # UndefinedBehaviorSanitizer (UBSan)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

add_executable(orbitalsim main.cpp OrbitalSim.cpp OrbitalBody.cpp orbitalSimView.cpp)

# Raylib
find_package(raylib CONFIG REQUIRED)

target_include_directories(orbitalsim PRIVATE ${raylib_INCLUDE_DIRS} raylib_cpp)
target_link_libraries(orbitalsim PRIVATE ${raylib_LIBRARIES} raylib_cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # From "Working with CMake" documentation:
    target_link_libraries(orbitalsim PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(orbitalsim PRIVATE m ${CMAKE_DL_LIBS}  pthread GL rt X11)
endif()


# Main test
enable_testing()

add_executable(orbitalsim_test main_test.cpp OrbitalSim.cpp OrbitalBody.cpp orbitalSimView.cpp)

add_test(NAME test1 COMMAND orbitalsim_test)

target_include_directories(orbitalsim_test PRIVATE ${raylib_INCLUDE_DIRS} raylib_cpp)
target_link_libraries(orbitalsim_test PRIVATE ${raylib_LIBRARIES} raylib_cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # From "Working with CMake" documentation:
    target_link_libraries(orbitalsim_test PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(orbitalsim_test PRIVATE m ${CMAKE_DL_LIBS}  pthread GL rt X11)
endif()