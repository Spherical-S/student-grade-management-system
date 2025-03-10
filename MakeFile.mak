GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --log-file=vallog

OBJS = #insert c files here
HDRS = #insert header files here
TARGET = prog1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) -o $(TARGET) $(OBJS)
	

test:
	#no tests exist yet

memory: $(VALGRIND) ./$(TARGET)
	grep "ERROR" vallog

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	/bin/rm -f *.o *~ $(TARGET) valog