BIN=httpd
CC=gcc
SRC=http.c main.c
OBJ=$(SRC:.c=.o)
#FLAGS=-D_DEBUG_
LDFLAGS=-lpthread

# 链接
$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# 编译
%.o : %.c
	$(CC) -c $< $(FLAGS) $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(OBJ) $(BIN)
