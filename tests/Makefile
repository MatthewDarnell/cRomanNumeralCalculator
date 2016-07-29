CC ?= clang
CFLAGS = -Wall -O3
DEFS =
INCLUDES = -I. -I../src
LIBS = -lcheck -lm -pthread -lrt
TARGET =
SRCS =	*.c ../src/*.c

all: parsing

parsing: $(SRCS)
	 $(CC) $(SRCS) $(CFLAGS) $(DEFS) -DPARSING $(INCLUDES) $(LIBS) -o parsing


clean:
	rm parsing
