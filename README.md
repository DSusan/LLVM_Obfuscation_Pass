# LLVM IR Transformation Passes
 LLVM  pass to obfuscate the control flow of a program at the LLVM IR level.

### Development Environment
- LLVM 18
- C++ compiler that supports C++17
- CMake 3.20 or higher

### Tools Needed
- clang-18 (for input generation)
- opt (to run the passes)

### Building the Passes
    export LLVM_DIR=<installation dir of llvm18>
    mkdir build
    cd build
    cmake -DLT_LLVM_INSTALL_DIR=$LLVM_DIR <source_dir>/LLVM_PASS/<pass directory>/
    make

### Generate Inputs
    $LLVM_DIR/bin/clang -O1 -S -emit-llvm <input source file> -o <IR output file>

### Run the Passes
    $LLVM_DIR/bin/opt -load-pass-plugin=<.so library> -passes=<"pass name"> -S <IR input file> -o <IR output file>

