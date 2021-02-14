all: main

main:
	rm -f main && $(CC) src/*.c -o main -O3 -Wall -pedantic -W -std=c99

dev:
	rm -f main && $(CC) src/*.c -o main -O3 -Wall -pedantic -W -std=c99

clean:
	rm -f main

