SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=main
CC:=gcc
CFLAGS:=-g
$(ELF):$(OBJS)
	gcc $^ -o $@
.PHONY:clean
clean:
	rm -f $(OBJS) $(ELF)
