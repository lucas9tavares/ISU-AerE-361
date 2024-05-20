INCLUDE_DIR := include
LIB_DIR := lib
SRC_DIR := src
BIN_DIR := bin
EXAMPLES_DIR := examples

all: $(BIN_DIR)/csvparse $(BIN_DIR)/usage_example_with_header $(BIN_DIR)/usage_example

$(BIN_DIR)/csvparse: $(SRC_DIR)/csv_matrix_parse.c $(INCLUDE_DIR)/csv.h
	gcc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(SRC_DIR)/csv_matrix_parse.c -Wl,-rpath='../$(LIB_DIR)' -lcsv -std=c99 -Wall -Werror -o $(BIN_DIR)/csvparse -g

$(BIN_DIR)/usage_example_with_header: $(EXAMPLES_DIR)/usage_example_with_header.c $(INCLUDE_DIR)/csv.h
	gcc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(EXAMPLES_DIR)/usage_example_with_header.c -Wl,-rpath='../$(LIB_DIR)' -lcsv -std=c99 -Wall -Werror -o $(BIN_DIR)/usage_example_with_header

$(BIN_DIR)/usage_example: $(EXAMPLES_DIR)/usage_example.c $(INCLUDE_DIR)/csv.h
	gcc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(EXAMPLES_DIR)/usage_example.c -Wl,-rpath='../$(LIB_DIR)' -lcsv -std=c99 -Wall -Werror -o $(BIN_DIR)/usage_example

clean:
	rm -rf $(BIN_DIR)/*
