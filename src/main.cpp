using namespace std;

#include <fstream>
#include <iostream>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS true
#define FAILURE false

#define MEM_LIM 32767
#define STACK_SIZE 512

#define NOP 0
#define OUT 1
#define IN 2
#define OUT_N 3
#define IN_N 4
#define ADD 5
#define SUB 6
#define JMP 7
#define JEZ 8
#define JGZ 9
#define JLZ 10
#define JNZ 11
#define MOVE 12
#define LOAD 13
#define SAVE 14
#define SET 15
#define KP 16
#define END 99

typedef struct inst {
  short op;
  short arg1;
  short arg2;
} inst;

typedef struct label {
  string text;
  short addr;
} label;

typedef struct machine {
  short a;
  short x;
  inst ir;
  short sp;
  short pc;
  short *memory;
} machine;

static machine mech;
static inst line[MEM_LIM];

#define STACK_PUSH(A) (stack[mech.sp++] = A)
#define STACK_POP() (stack[--mech.sp])
#define STACK_EMPTY() (mech.sp == 0)
#define STACK_FULL() (mech.sp == STACK_SIZE)

static short stack[STACK_SIZE];

static label list[1024];

int assemble() {
  short count;
  string x;
  short y;
  ifstream file;
  file.open("tmp2.prgm");
  while (!file.eof()) {
    file >> x;
    if (x == "end") {
      line[count].op = END;
    } else if (x == "add") {
      line[count].op = ADD;
      file >> y;
      line[count].arg1 = y;
    } else if (x == "sub") {
      line[count].op = SUB;
      file >> y;
      line[count].arg1 = y;
    } else if (x == "out") {
      line[count].op = OUT;
    } else if (x == "out_n") {
      line[count].op = OUT_N;
    } else if (x == "in") {
      line[count].op = OUT;
    } else if (x == "in_n") {
      line[count].op = OUT_N;
    } else if (x == "jmp") {
      line[count].op = JMP;
      file >> y;
      line[count].arg1 = y - 1;
    } else if (x == "move") {
      line[count].op = MOVE;
      file >> y;
      line[count].arg1 = y;
      file >> y;
      line[count].arg2 = y;
    } else if (x == "load") {
      line[count].op = LOAD;
      file >> y;
      line[count].arg1 = y;
    } else if (x == "save") {
      line[count].op = SAVE;
      file >> y;
      line[count].arg1 = y;
    } else if (x == "set") {
      line[count].op = SET;
      file >> y;
      line[count].arg1 = y;
    }
    count++;
  }
  return SUCCESS;
}

int branch() {
  ifstream in("tmp.prgm");
  short addr = 0, ind = 0;
  string instr;
  while (!in.eof()) {
    in >> instr;
    if (instr == "lbl") {
      in >> instr;
      list[ind].text = instr;
      list[ind].addr = addr;
      ind++;
    }
    addr++;
  }
  in.close();
  return 0;
}

int format(char *filename) {
  ifstream in(filename);
  ofstream out("tmp.prgm");
  string str, str1;
  while (!in.eof()) {
    in >> str;
    if (str[0] == '\'') {
      out << ((short)str[1]);
    } else if (str == "\n") {
      continue;
    } else {
      out << str;
    }
    out << " ";
  }
  branch();
  in.close();
  out.close();
  in.open("tmp.prgm");
  out.open("tmp2.prgm");
  while (!in.eof()) {
    in >> str;
    if (str == "jmp") {
      out << str;
      out << " ";
      in >> str1;
      for (short i = 0; i < 1024; i++) {
        if (str1 == list[i].text) {
          out << list[i].addr;
          out << " ";
        }
      }
    } else {
      out << str;
      out << " ";
    }
  }
  in.close();
  out.close();
  return SUCCESS;
}

int preprocess(char *filename) {
  format(filename);
  return SUCCESS;
}

int compile(char *filename) {
  if (!preprocess(filename)) {
    return FAILURE;
  }
  if (!assemble()) {
    return FAILURE;
  }
  return SUCCESS;
}

int execute() {
  while (line[mech.pc].op != END) {
    if (line[mech.pc].op == OUT) {
      putchar(mech.a);
    } else if (line[mech.pc].op == IN) {
      mech.a = getchar();
    } else if (line[mech.pc].op == ADD) {
      mech.a += line[mech.pc].arg1;
    } else if (line[mech.pc].op == SUB) {
      mech.a -= line[mech.pc].arg1;
    } else if (line[mech.pc].op == OUT_N) {
      cout << mech.a;
    } else if (line[mech.pc].op == IN_N) {
      cin >> mech.a;
    } else if (line[mech.pc].op == JMP) {
      mech.pc = line[mech.pc].arg1 - 1;
    } else if (line[mech.pc].op == MOVE) {
      mech.memory[line[mech.pc].arg2] = mech.memory[line[mech.pc].arg1];
    } else if (line[mech.pc].op == LOAD) {
      mech.a = mech.memory[line[mech.pc].arg1];
    } else if (line[mech.pc].op == SAVE) {
      mech.memory[line[mech.pc].arg1] = mech.a;
    } else if (line[mech.pc].op == SET) {
      mech.a = line[mech.pc].arg1;
    }
    mech.pc++;
  }
  return SUCCESS;
}

int main(int argc, char *argv[]) {
  mech.a = 0;
  mech.x = 0;
  mech.sp = 0;
  mech.pc = 0;
  mech.memory = (short *)malloc(MEM_LIM * sizeof(short));
  if (!compile(argv[1])) {
    printf("An error occurred during reading.");
  }
  if (!execute()) {
    printf("An error occurred during execution.");
  }
  cout << endl;
  return 0;
}