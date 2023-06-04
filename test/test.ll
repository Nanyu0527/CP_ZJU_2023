; ModuleID = 'main'
source_filename = "main"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

declare i32 @gets(...)

define i32 @main() {
entry:
  %0 = alloca i32, align 4
  %c = alloca i8, align 1
  store i8 115, i8* %c, align 1

return:                                           ; No predecessors!
  %1 = load i32, i32* %0, align 4
  ret i32 %1
}
