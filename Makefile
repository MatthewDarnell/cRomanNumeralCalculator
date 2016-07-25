CC ?= clang
CFLAGS = -Wall -O3
DEFS =
INCLUDES = -Isrc
TEST_INCLUDES = -Itests
LIBS = -lcheck -lm -pthread -lrt
TARGET =
SRCS =	src/*.c
TEST_SRCS = tests/*.c
TEST_DIR = tests/


all: tests


tests: parsing
parsing: $(SRCS)
	 $(CC) $(SRCS) $(TEST_SRCS) $(CFLAGS) $(DEFS) -DPARSING $(INCLUDES) $(TEST_INCLUDES) $(LIBS) -o $(TEST_DIR)parsing


clean:
	rm $(TEST_DIR)parsing
