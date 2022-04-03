# Name of the project
PROJECT_NAME = Assembler

#Check Operating System
ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif

#Hex file output directory
OUTPUT = output

# Build Output directory
BUILD = build

# All source code files
SRC = src/Instruction_Process_Methods.c\
src/Instruction_to_Hex.c\
src/Project_main.c\

TEST_SRC = src/Instruction_Process_Methods.c\
src/Instruction_to_Hex.c\
test/Unit_test_Assembler.c\
unity/unity.c\

TEST_OUTPUT = $(BUILD)/Test_$(PROJECT_NAME).$(EXEC)

# All include folders with header files
INC	= -Iinc\
-Iunity\

#Library Inlcudes
INCLUDE_LIBS = -lcunit

# Project Output name
PROJECT_OUTPUT = $(BUILD)/$(PROJECT_NAME).$(EXEC)

# Document files
DOCUMENTATION_OUTPUT = documentation/html documentation/rtf

# Default target built
$(PROJECT_NAME):all

# Run the target even if the matching name exists
.PHONY: run clean test doc all

all: $(SRC) $(BUILD) $(OUTPUT)
	gcc  $(SRC) $(INC) -o $(call FixPath,$(BUILD)/$(PROJECT_NAME).$(EXEC))

# Call `make run` to run the application
run:$(PROJECT_NAME)
	$(call FixPath,$(BUILD)/$(PROJECT_NAME).$(EXEC))

# Build and Run Unity Tests
test: $(BUILD)
	gcc $(TEST_SRC) $(INC) -o $(TEST_OUTPUT) $(INCLUDE_LIBS)
	./$(TEST_OUTPUT)

# Document the code using Doxygen
doc:
	make -C ./documentation

# Open the doxygen created Webpage in Browser
doc_run:
	make run -C ./documentation 
# Analyze the code using memceck staticceck code-coverage and sanitize_check
analyze: test memcheck staticcheck coverage sanitize_check

# Cppcheck
staticcheck: $(BUILD)
	cppcheck --enable=all -iunity .

# Memory Checks
memcheck: $(BUILD)
	valgrind ./$(TEST_OUTPUT)

# Sanitize Check
sanitize_check: $(BUILD)
	gcc -fsanitize=address -fno-omit-frame-pointer $(TEST_SRC) $(INC) -o $(TEST_OUTPUT) $(INCLUDE_LIBS)
	./$(TEST_OUTPUT)

# Code Coverage
coverage:$(TEST_SRC)
	gcc -fprofile-arcs -ftest-coverage $(TEST_SRC) $(INC) -o $(TEST_OUTPUT) $(INCLUDE_LIBS)
	./$(TEST_OUTPUT)
	gcov -a Project_main.c

# Remove all the built files, invoke by `make clean`
clean:
	$(RM) $(BUILD) output *.gcda *.gcno *.gcov

clean_doc:
	$(RM) $(DOCUMENTATION_OUTPUT)
	
# Create new build folder if not present
$(BUILD):
	mkdir build

$(OUTPUT):
	mkdir output