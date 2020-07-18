all:
	@gcc main.c Graph.c -o main.exe -I -ansi -Wall

run:
	@./main.exe
