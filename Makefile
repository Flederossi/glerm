glerm:
	$(CC) -std=c99 src/*.c -o bin/glerm

run: glerm
	./bin/glerm
