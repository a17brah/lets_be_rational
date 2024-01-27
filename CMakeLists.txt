cmake_minimum_required(VERSION 3.26)

if (NOT SKBUILD)
    message(WARNING "This CMake file should be executed via scikit-build. "
            "Please run\n$ pip install .")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/src/*.cpp")

# Try to import all Python components potentially needed by nanobind
find_package(Python 3.8
        REQUIRED COMPONENTS Interpreter Development.Module
        OPTIONAL_COMPONENTS Development.SABIModule)

# Import nanobind through CMake's find_package mechanism
add_subdirectory(ext/nanobind)
find_package(nanobind CONFIG REQUIRED)
include_directories("${NB_DIR}/include")
include_directories("${_Python_INCLUDE_DIR}")

nanobind_add_module(_lets_be_rational_core NB_STATIC
        src/export.cpp
        src/src/erf_cody.cpp
        src/src/lets_be_rational.cpp
        src/src/normal_distribution.cpp
        src/src/rational_cubic.cpp)

target_include_directories(
        _lets_be_rational_core
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

find_package(OpenMP)
target_link_libraries(_lets_be_rational_core PUBLIC OpenMP::OpenMP_CXX)

add_executable(test main.cpp src/src/erf_cody.cpp
        src/src/lets_be_rational.cpp
        src/src/normal_distribution.cpp
        src/src/rational_cubic.cpp)

target_include_directories(
        test
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_property(TARGET _lets_be_rational_core PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(_lets_be_rational_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _lets_be_rational_core LIBRARY DESTINATION .)
