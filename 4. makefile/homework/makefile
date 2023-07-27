src = $(wildcard ./src/*.c)  					 # ./src/add.c ./src/sub.c ...
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))   # ./obj/add.o  ./obj/sub.o  ...
out = $(patsubst ./src/%.c, ./out/%, $(src))   # ./out/add  ./out/sub  ...

inc_path = ./inc


myArgs = -Wall -g

ALL: a.out

a.out: ${obj}
	gcc $^ -o $@ $(myArgs)

$(out): ./out%: ./obj%.o
	gcc $^ -o $@ $(myArgs)

$(obj): ./obj%.o: ./src%.c
	gcc -c $< -o $@ $(myArgs) -I $(inc_path) # 预处理阶段加头文件参数

clean:
	-rm -rf $(obj) $(out) a.out

.PHONY: clean ALL
