cmake_minimum_required(VERSION 3.18...3.26)

project(py_lets_be_rational LANGUAGES CXX)

if (NOT SKBUILD)
    message(WARNING "This CMake file should be executed via scikit-build. "
            "Please run\n$ pip install .")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/src/*.cpp")

# Try to import all Python components potentially needed by nanobind
if (SKBUILD)
    # Constrain FindPython to find the Python version used by scikit-build
    set(Python_VERSION "${PYTHON_VERSION_STRING}")
    set(Python_EXECUTABLE "${PYTHON_EXECUTABLE}")
    set(Python_INCLUDE_DIR "${PYTHON_INCLUDE_DIR}")
    set(Python_LIBRARIES "${PYTHON_LIBRARY}")
elseif (MSVC)
    # MSVC needs a little extra help finding the Python library
    find_package(PythonInterp)
    find_package(Python)
endif()

if (UNIX AND NOT APPLE)
    find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
else()
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
endif()

# Import nanobind through CMake's find_package mechanism
# Run `nanobind.cmake_dir()` from Python to detect install location
execute_process(
        COMMAND
        "${PYTHON_EXECUTABLE}" -c "import nanobind; print(nanobind.cmake_dir())"
        OUTPUT_VARIABLE _tmp_dir
        OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT)
list(APPEND CMAKE_PREFIX_PATH "${_tmp_dir}")
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

set_property(TARGET _lets_be_rational_core PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(_lets_be_rational_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _lets_be_rational_core LIBRARY DESTINATION .)
