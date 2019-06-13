DIR_OUTPUT = ./bin
DIR_SRC = ./src
NAME_EXE_1 = lab2
NAME_EXE_2 = functions

all: release

run:
#	$(DIR_OUTPUT)/$(NAME_EXE_1).out
	$(DIR_OUTPUT)/$(NAME_EXE_1).out -i test_files/visibilidades.csv -o propiedades.txt -d 20 -n 4 -b

release:
	mkdir -p $(DIR_OUTPUT)
	gcc $(DIR_SRC)/lab1.c -o $(DIR_OUTPUT)/$(NAME_EXE_1).out -lm -O2
	gcc $(DIR_SRC)/Vis.c -o $(NAME_EXE_2).out -lm -O2

debug:
	mkdir -p $(DIR_OUTPUT)
	gcc $(DIR_SRC)/lab1.c -o $(DIR_OUTPUT)/$(NAME_EXE_1) -lm -g3 -Wall -pedantic -DDEBUG
	gcc $(DIR_SRC)/Vis.c -o $(DIR_OUTPUT)/$(NAME_EXE_2) -lm -g3 -Wall -pedantic -DDEBUG

clean:
	rm -rf $(DIR_OUTPUT)
	rm $(NAME_EXE_2).out

