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

# raylib: required for macOS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_STANDARD 11)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

# Main executable
add_executable(orbitalsim main.cpp orbitalSim.cpp orbitalSimView.cpp)

# Raylib
find_package(raylib CONFIG REQUIRED)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_include_directories(orbitalsim PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_libraries(orbitalsim PRIVATE ${RAYLIB_LIBRARIES})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(orbitalsim PRIVATE raylib)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(orbitalsim PRIVATE raylib raylib_cpp m ${CMAKE_DL_LIBS} pthread GL rt X11)
endif()


# Main test
enable_testing()

add_executable(orbitalsim_test main_test.cpp orbitalSim.cpp)

add_test(NAME test1 COMMAND orbitalsim_test)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_include_directories(orbitalsim_test PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_libraries(orbitalsim_test PRIVATE ${RAYLIB_LIBRARIES})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(orbitalsim_test PRIVATE raylib)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(orbitalsim_test PRIVATE raylib raylib_cpp m ${CMAKE_DL_LIBS} pthread GL rt X11)
endif()


# raylib: required for macOS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(orbitalsim PRIVATE "-framework IOKit")
    target_link_libraries(orbitalsim PRIVATE "-framework Cocoa")
    target_link_libraries(orbitalsim PRIVATE "-framework OpenGL")
endif()