GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --log-file=vallog

OBJS = main.o student.o readCSV.o unitTests.o
HDRS = student.h myheader.h
TARGET = prog1

EXPECTED_DIR = expected
OUTPUT_DIR = output

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) -o $(TARGET) $(OBJS)
	

test:
	@for i in $(shell seq 0 5); do \
		echo Running test: $$i; \
		./$(TARGET) $$i > $(OUTPUT_DIR)/test$$i; \
		if diff -b $(EXPECTED_DIR)/test$$i $(OUTPUT_DIR)/test$$i; then \
			echo "Test $$i PASSED"; \
		else \
			echo "Test $$i FAILED"; \
		fi; \
	done

memory: $(TARGET)
	$(VALGRIND) ./$(TARGET)
	grep "ERROR" vallog

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	/bin/rm -f *.o *~ $(TARGET) valog $(OUTPUT_DIR)/*