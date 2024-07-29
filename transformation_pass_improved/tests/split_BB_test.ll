; split_BB_test.ll
; RUN: /usr/lib/llvm-18/bin/opt -load-pass-plugin /mnt/c/Users/carli/OneDrive/Escritorio/DS/LLVM_Pass/transformation_pass_improved/build/libllvm-transformation-pass-improved.so -passes="split-pass" < %s -S | /usr/lib/llvm-18/bin/FileCheck %s

define void @test_split() {
; CHECK-LABEL: @test_split
entry:
  %0 = alloca i32, align 4
  ; CHECK: br label %entry.split
  br label %entry.split

entry.split: ; preds = %entry
  ; CHECK: entry.split:
  ; CHECK-NOT: %0 = alloca i32, align 4
  ; The first instruction should now be in a new block
  %1 = alloca i32, align 4
  ret void
}