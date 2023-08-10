src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))

ALL: $(target)

%: %.c
	gcc $< -o $@ -g -Wall -lpthread

clean:
	-rm -rf $(target)

.PHONY: clean ALL
