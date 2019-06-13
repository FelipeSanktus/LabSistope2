DIR_OUTPUT = ./bin
DIR_SRC = ./src
NAME_EXE_1 = lab2
HEADERS = src/functions.h src/structs/Monitor.h src/structs/Results.h
SOURCE_FILES = src/functions.c src/structs/Monitor.c src/structs/Results.c


all: $(DIR_SRC)/lab2.c $(HEADERS)
	gcc $(DIR_SRC)/lab2.c -o $(DIR_OUTPUT)/$(NAME_EXE_1).out $(SOURCE_FILES) -lm -O2
	mkdir -p $(DIR_OUTPUT)

run:
	$(DIR_OUTPUT)/$(NAME_EXE_1).out -i test_files/test.csv -o propiedades.txt -d 20 -n 4 -s 3 -b

debug:
	mkdir -p $(DIR_OUTPUT)
	$(DIR_SRC)/lab2.c $(DIR_OUTPUT)/$(NAME_EXE_1).out $(HEADERS)
	gcc $(DIR_SRC)/lab2.c -o $(DIR_OUTPUT)/$(NAME_EXE_1).out $(SOURCE_FILES) -lm -g3 -Wall -pedantic -DDEBUG

clean:
	rm -rf $(DIR_OUTPUT)

