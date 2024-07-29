# LLVM IR Transformation Passes
LLVM  pass to obfuscate the control flow of a program at the LLVM IR level.
There are three different passes inside the repository:
- **hello_world_example:** Simple analysis pass added to test the environment and tools before running the transformation passes.
- **transformation_pass:** Transformation pass that splits each basic block in a function into two basic blocks and link the two with an unconditional branch.
- **transformation_pass_improved:** Transformation pass improved by introducing a bogus/made-up conditional branch instead of an unconditional branch when splitting basic blocks.

### Development Environment
- LLVM 18
- C++ compiler that supports C++17
- CMake 3.20 or higher

### Tools Needed
- clang-18 (for input generation)
- opt (to run the passes)
- FileCheck and lit (for tests)

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

In order to run the "transformation_pass_improved" pass with conditional branches, the flag **-use-conditional** needs to be specified when using opt:

    $LLVM_DIR/bin/opt -load-pass-plugin=libLLVMSplitPass.so -passes="split-pass" -use-conditional -S <IR input file> -o <IR output file>

Removing the flag will use unconditional branches instead.

### Automatic Test
Before doing the test, verify the paths to llvm installation and tools in run_tests.sh and the llvm binaries location in lit.cfg, then simply do:

    ./run_tests.sh

To get the output of the test you can also run:

    lit -v ./ > ./Output/lit_output.txt 2>&1

Sample output is inside  transformation_pass_improved/tests/Output directory.