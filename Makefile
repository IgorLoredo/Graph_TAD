all:
	@gcc main.c Queue.c Graph.c -o main.exe -I -lm -ansi -g -Wall

run:
	@./main.exe
