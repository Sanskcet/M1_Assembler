# Name of the project
PROJECT_NAME = Assembler

# Output directory
BUILD = build

# All source code files
SRC = src/Instruction_Process_Methods.c\
src/Instruction_to_Hex.c\
src/Project_main.c\

TEST_SRC = src/Instruction_Process_Methods.c\
src/Instruction_to_Hex.c\
test/Unit_test_Assembler.c\
unity/unity.c\

TEST_OUTPUT = $(BUILD)/Test_$(PROJECT_NAME).out

# All include folders with header files
INC	= -Iinc\
-Iunity\

#Library Inlcudes
INCLUDE_LIBS = -lcunit

# Project Output name
PROJECT_OUTPUT = $(BUILD)/$(PROJECT_NAME).out

# Document files
DOCUMENTATION_OUTPUT = documentation/html

# Default target built
$(PROJECT_NAME):all

# Run the target even if the matching name exists
.PHONY: run clean test doc all

all: $(SRC) $(BUILD)
	gcc $(SRC) $(INC) -o $(PROJECT_OUTPUT).out

# Call `make run` to run the application
run:$(PROJECT_NAME)
	./$(PROJECT_OUTPUT).out

# Build and Run Unity Tests
test: $(BUILD)
	gcc $(TEST_SRC) $(INC) -o $(TEST_OUTPUT) $(INCLUDE_LIBS)
	./$(TEST_OUTPUT)

# Document the code using Doxygen
doc:
	make -C ./documentation

# Remove all the built files, invoke by `make clean`
clean:
	rm -rf $(BUILD) output *.gcda *.gcno *.gcov

clean_doc:
	rm -rf $(DOCUMENTATION_OUTPUT)
	
# Create new build folder if not present
$(BUILD):
	mkdir build