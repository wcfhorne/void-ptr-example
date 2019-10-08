# makefile for VoidPtr Example 
# this is not a generic makefile and I recommend that 
# you look up how to make one, or find a program that will
# write one for you

CC = gcc
FLG = -Wall -Wextra -Werror
OBJ = main.o ref.o linked_list.o 
PRG = prg 
LIB =
SRC = ./src

$(PRG): $(OBJ)
	$(CC) $(FLG) $(OBJ) $(LIB) -o $@

main.o: main.c 
	$(CC) $(FLG) $(LIB) -c $^ -o $@

ref.o: ref.c
	$(CC) $(FLG) $(LIB) -c $^ -o $@

linked_list.o: linked_list.c
	$(CC) $(FLG) $(LIB) -c $^ -o $@

cleano:
	rm $(OBJ)

clean:
	rm $(OBJ) $(PRG)
