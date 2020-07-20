CC=gcc
target=xhttpd
inc=./include

src=$(wildcard ./src/*.c)
obj=$(patsubst %.c,%.o,$(src))


$(target):$(obj)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -I $(inc) -o $@

.PHONY:clean_o
clean_o:
	-rm -rf $(obj)
.PHONE:clean_target
clean_target:
	-rm -rf $(target)
