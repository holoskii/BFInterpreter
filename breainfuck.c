#include <stdio.h>
#include <string.h>

#define PROGRAM_SIZE 32768
#define STACK_SIZE 512
#define DATA_SIZE 4096

char cmd[PROGRAM_SIZE];
char *brackets[PROGRAM_SIZE];
int stack[STACK_SIZE];
int data[DATA_SIZE];

int brainfuck(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        printf("File %s not found\n", filename);
        return 1;
    }

    int* sp = stack;
    int* i_data = data;
    char c;
    char *ptr = cmd;

    do {
        c = (char)getc(fin);
        if (c == '#') while (c != '\n') c = (char)getc(fin);
        if (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']') {
            *ptr = c;
            if (*ptr == '[') {
                *sp++ = ptr - cmd;
            } else if (*ptr == ']') {
                brackets[ptr - cmd] = cmd + *(--sp);
                brackets[*sp] = ptr;
            }
            ptr++;
        }
    } while (c != EOF);
    fclose(fin);

    memset(data, 0, sizeof(data));
    for (ptr = cmd; *ptr != 0; ptr++) {
        switch (*ptr) {
            case '>': i_data++; break;
            case '<': i_data--; break;
            case '+': (*i_data)++; break;
            case '-': (*i_data)--; break;
            case '.': putchar(*i_data); break;
            case ',': printf("\ninput:"); *i_data = getchar(); break;
            case '[': if (!*i_data) ptr = brackets[ptr - cmd]; break;
            case ']': if (*i_data) ptr = brackets[ptr - cmd]; break;
        }
    }
    printf("\n");
	return 0;
}

int main(int argc, char** agrv) {
    if (argc > 1) {
        brainfuck(agrv[1]);
    } else {
        printf("Input filename as argument");
    }

    // brainfuck("hello_world.bf");
    // brainfuck("fibonacci.bf");
    // brainfuck("factorial.bf");
    // brainfuck("99bottles.bf");
}