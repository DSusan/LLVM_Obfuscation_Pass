#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

// Command-line options
static cl::opt<bool> UseConditionalBranch("use-conditional", cl::desc("Use conditional branch instead of unconditional branch"), cl::init(false));

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

        if (UseConditionalBranch) {
            LLVMContext &Context = BB->getContext();
            IRBuilder<> Builder(BB);

            // Hardcoded condition (x < 10 || x * (x + 1) % 2 == 0)
            Value *LHS = ConstantInt::get(Type::getInt32Ty(Context), 0);
            Value *RHS = ConstantInt::get(Type::getInt32Ty(Context), 1);
            Value *Cond = Builder.CreateICmpEQ(LHS, RHS);

            // Duplicate the New Basic Block to redirect into the false branch destination
            BasicBlock *FalseBB = BasicBlock::Create(Context, BB->getName() + ".false", &F, NewBB);
            IRBuilder<> FalseBuilder(FalseBB);
            FalseBuilder.CreateBr(NewBB);

            // Create the conditional branch
            Builder.CreateCondBr(Cond, NewBB, FalseBB);

            // Remove the old terminator
            BB->getTerminator()->eraseFromParent();
        } else {
            // Create an unconditional branch to the new basic block
            IRBuilder<> Builder(BB);
            Builder.CreateBr(NewBB);

            // Remove the old terminator
            BB->getTerminator()->eraseFromParent();
        }
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














