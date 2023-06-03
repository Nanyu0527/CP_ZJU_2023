; ModuleID = 'main'
source_filename = "main"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

declare i32 @gets(...)

define i32 @main() {
entry:
  %0 = alloca i32, align 4

return:                                           ; No predecessors!
  %1 = load i32, i32* %0, align 4
  ret i32 %1
}
