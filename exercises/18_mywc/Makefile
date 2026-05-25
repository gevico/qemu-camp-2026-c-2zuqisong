CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = 18_mywc
SRCS = 18_mywc.c mywc.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

# 1. 链接规则：将所有的 .o 目标文件链接成最终的可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 2. 编译规则：将每一个 .c 文件编译成对应的 .o 目标文件
%.o: %.c mywc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean