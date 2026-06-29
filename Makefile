main.o:
	gcc -c main.c

proj: main.o util.o
	gcc main.o util.o -o proj

clean:
	rm util.o main.o proj

util.o:
	gcc -c util.c

run: proj
	./proj