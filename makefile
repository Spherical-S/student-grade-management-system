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
	@for input_file in $(INPUT_DIR)/*; do \
		output_file=$(OUTPUT_DIR)/$(notdir $(input_file)); \
		expected_file=$(EXPECTED_DIR)/$(notdir $(input_file)); \
		echo "Running test for $$input_file"; \
		./$(TARGET) < $$input_file > $$output_file; \
		if diff -q $$output_file $$expected_file; then \
			echo "Test passed for $$input_file"; \
		else \
			echo "Test failed for $$input_file"; \
		fi; \
	done

memory: $(VALGRIND) ./$(TARGET)
	grep "ERROR" vallog

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	/bin/rm -f *.o *~ $(TARGET) valog $(OUTPUT_DIR)/*