all:
	@gcc main.c Graph.c -o main.exe -I -Wall

run:
	@./main.exe