all:
	@gcc main.c Queue.c Graph.c -o main.exe -I -ansi -Wall

run:
	@./main.exe
