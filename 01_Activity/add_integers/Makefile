TEST_FILE = test/test_add_integers.c\

BUILD=build

INC	= -Isrc\
-Iunity\

BUILD_FILES = src/add_integers.c\
unity/unity.c\

all: $(BUILD)
	gcc $(TEST_FILE) $(BUILD_FILES) $(INC) -o ./output/sum.out -lcunit

run:
	./output/sum.out

clean: 
	rm -rf output

$(BUILD):
	mkdir -p output