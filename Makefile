CC=g++
SRC=src/main.cpp

make:
	$(CC) $(SRC) -o machine

debug:
	$(CC) $(SRC) -g -o machine

cleanup:
	clang-format src/main.cpp > tmp.txt
	cat tmp.txt > src/main.cpp
	rm tmp.txt

clean:
	rm -rf build