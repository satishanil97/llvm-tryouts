#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"

using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "I saw a function called " << F.getName() << "!\n";
      F.dump();
      //return false;
	std::vector<void*> domain;

      for(auto& B : F) {
	      errs()<< "I saw a basic block\n";
	      for(auto& I : B) {
			errs()<< typeof(I);
		      errs()<< "I saw an instruction\n";
			if (auto* op = dyn_cast<BinaryOperator>(&I)) {
				errs() << "I saw a binary operator\n";
				bool found = false;
				for(void* element : domain) {
					if(element == op) {
						found = true;
						break;
					}
				}
				if(found == false) {
					domain.push_back(op);
				}
			}
	      }      
      }

	for(void* element : domain) {
		errs()<< element <<"\n";
	}
      
    }
  };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
