TARGET = gr8
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

default: $(TARGET)
all: default

EXCLUDES = %_tests.o
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS = $(filter-out $(EXCLUDES),$(OBJS))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@


test: gr_tests.o 
	./gr_tests.o

gr_tests.o: $(OBJS)
	$(CC) minunit_tests.o googlereader.o -Wall $(LIBS) -o $@


clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY: default clean test
