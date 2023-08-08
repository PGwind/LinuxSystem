gcctest1.c 为正确代码，用来基础调试
gcctest2.c 为调试代码，用来进阶调试

# test1.c 部分
gcc test1.c -o gcctest1  # gcctest1 无法调试
gcc test1.c -o a.out -g  # -g 使用该参数编译可执行文件，得到调试表

调试 a.out进行基础命令学习


# test2.c 部分
gcc test2.c -o gcctest2  # gcctest2 无法调试
gcc test2.c -o b.out -g  # b.out

调试 b.out、c.out ... 等进行进阶命令学习

b.out 为 段错误，使用 r 查找
c.out 为 main参数调试

