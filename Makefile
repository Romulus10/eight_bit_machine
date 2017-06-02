CC=gcc
ASM_SRC=src/assembler/main.c
MCH_SRC=src/machine/main.c

make:
	mkdir -p build/release
	$(CC) $(ASM_SRC) -o build/release/assembler
	$(CC) $(MCH_SRC) -o build/release/machine

debug:
	mkdir -p build/debug
	$(CC) $(ASM_SRC) -g -o build/debug/assembler
	$(CC) $(MCH_SRC) -g -o build/debug/machine

clean:
	rm -rf build