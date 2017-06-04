CC=g++
SRC=src/main.c

make:
	mkdir -p build/release
	$(CC) $(SRC) -o build/release/machine

debug:
	mkdir -p build/debug
	$(CC) $(SRC) -g -o build/debug/machine

clean:
	rm -rf build