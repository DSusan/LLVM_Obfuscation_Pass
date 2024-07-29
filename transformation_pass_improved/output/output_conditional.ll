; ModuleID = '/mnt/c/Users/carli/OneDrive/Escritorio/DS/LLVM_Pass/transformation_pass_improved/inputs/test.ll'
source_filename = "/mnt/c/Users/carli/OneDrive/Escritorio/DS/LLVM_Pass/transformation_pass_improved/inputs/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@str = private unnamed_addr constant [7 x i8] c"Lesser\00", align 1

; Function Attrs: nofree nounwind uwtable
define dso_local void @test() local_unnamed_addr #0 {
  br label %.split

.false:                                           ; No predecessors!
  br label %.split

.split:                                           ; preds = %.false, %0
  %1 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str)
  ret void
}

; Function Attrs: nofree nounwind uwtable
define dso_local noundef i32 @main() local_unnamed_addr #0 {
  br label %.split

.false:                                           ; No predecessors!
  br label %.split

.split:                                           ; preds = %.false, %0
  %1 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str)
  ret i32 0
}

; Function Attrs: nofree nounwind
declare noundef i32 @puts(ptr nocapture noundef readonly) local_unnamed_addr #1

attributes #0 = { nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
