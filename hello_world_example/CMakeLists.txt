cmake_minimum_required(VERSION 3.20)
project(llvm-tutor-hello-world)

#===============================================================================
# 1. LOAD LLVM CONFIGURATION
#===============================================================================
# Set this to a valid LLVM installation dir
# Set this to a valid LLVM installation dir
set(LT_LLVM_INSTALL_DIR "C:/Users/carli/OneDrive/Escritorio/DS/LLVM/llvm-project/build" CACHE PATH "Path to LLVM installation")

# Add the location of LLVMConfig.cmake to CMake search paths (so that find_package can locate it)
list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

# Debugging: print CMAKE_PREFIX_PATH
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

find_package(LLVM CONFIG REQUIRED)
if(NOT LLVM_FOUND)
  message(FATAL_ERROR "Could not find LLVM package")
endif()

# Debugging: print LLVM_VERSION_MAJOR
message(STATUS "Found LLVM version ${LLVM_VERSION_MAJOR}")

if("${LLVM_VERSION_MAJOR}" VERSION_LESS 18)
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 18 or above")
endif()

# HelloWorld includes headers from LLVM - update the include paths accordingly
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

#===============================================================================
# 2. LLVM-TUTOR BUILD CONFIGURATION
#===============================================================================
# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

#===============================================================================
# 3. ADD THE TARGET
#===============================================================================
add_library(HelloWorld SHARED HelloWorld.cpp)

# Allow undefined symbols in shared objects on Darwin (this is the default behaviour on Linux)
target_link_libraries(HelloWorld
  "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")
