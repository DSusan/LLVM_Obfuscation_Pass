# LLVM IR Transformation Pass
 LLVM  pass to obfuscate the control flow of a program at the LLVM IR level.

### Development Environment
- LLVM 18
- C++ compiler that supports C++17
- CMake 3.20 or higher

### Tools Needed
- clang-18 (for input generation)
- opt (to run the passes)

### Building the Pass
    export LLVM_DIR=<installation dir of llvm18>
    mkdir build
    cd build
    cmake -DLT_LLVM_INSTALL_DIR=$LLVM_DIR <source_dir>/LLVM_PASS/transformation_pass/
    make
