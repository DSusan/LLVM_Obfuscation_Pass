#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

class SplitPass : public PassInfoMixin<SplitPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
};

PreservedAnalyses SplitPass::run(Function &F, FunctionAnalysisManager &FAM) {
    std::vector<BasicBlock *> OriginalBlocks;

    // Get all original basic blocks
    for (auto &BB : F) {
        OriginalBlocks.push_back(&BB);
    }

    // Iterate and split each basic block
    for (auto *BB : OriginalBlocks) {
        if (BB->empty()) continue;

        Instruction *SplitInst = &*BB->getFirstInsertionPt();
        BasicBlock *NewBB = BB->splitBasicBlock(SplitInst, BB->getName() + ".split");

        IRBuilder<> Builder(BB);
        Builder.CreateBr(NewBB);
        BB->getTerminator()->eraseFromParent();
    }

    return PreservedAnalyses::all();
}
// Register the pass
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "SplitPass", LLVM_VERSION_STRING, [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "split-pass") {
                        FPM.addPass(SplitPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
