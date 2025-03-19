GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --log-file=vallog

OBJS = main.o student.o readCSV.o unitTests.o
HDRS = student.h myheader.h
TARGET = prog1

INPUT_DIR = input
EXPECTED_DIR = expected
OUTPUT_DIR = output

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) -o $(TARGET) $(OBJS)
	

test:
	@for file in $(INPUT_DIR)/; do \
		echo "Running test for $$file"; \
		./$(TARGET) < $$file > $(OUTPUT_DIR)/$$file; \
		diff $$file $(EXPECTED_DIR)/$$file; \
		if [ $$? -ne 0 ]; then \
			echo "Test failed for $$file"; \
		else \
			echo "Test passed for $$file"; \
		fi \
	done

memory: $(VALGRIND) ./$(TARGET)
	grep "ERROR" vallog

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	/bin/rm -f *.o *~ $(TARGET) valog $(OUTPUT_DIR)/*