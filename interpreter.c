#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <conio.h>
#else
	#include <stdio.h>
	#include <termios.h>
	#include <unistd.h>

	int getch(void) {
		struct termios oldattr, newattr;
		int ch;

		tcgetattr(STDIN_FILENO, &oldattr);
		newattr = oldattr;
		newattr.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

		ch = getchar();

		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

		return ch;
	}
#endif

#define MAX_CODE_LENGTH 1000
#define MAX_STACK_SIZE 1000

typedef struct {
	char code[MAX_CODE_LENGTH];
	int code_length;
} Program;

typedef struct {
	int stack[MAX_STACK_SIZE];
	int top;
} Stack;

void initialize_stack(Stack *stack) {
	stack->top = -1;
}

void push(Stack *stack, int value) {
	stack->top++;
	stack->stack[stack->top] = value;
}

int pop(Stack *stack) {
	int value = stack->stack[stack->top];
	stack->top--;
	return value;
}

void execute(Program *program) {
	Stack stack;
	initialize_stack(&stack);

	int ip = 0;
	while (ip < program->code_length) {
		char instruction = program->code[ip];

		switch (instruction) {
			case '+':
				push(&stack, pop(&stack) + pop(&stack));
				break;
			case '-':
				push(&stack, pop(&stack) - pop(&stack));
				break;
			case '*':
				push(&stack, pop(&stack) * pop(&stack));
				break;
			case '/':
				push(&stack, pop(&stack) / pop(&stack));
				break;
			case 'n':
				printf("%d\n", pop(&stack));
				break;
			default:
				if (instruction >= '0' && instruction <= '9') {
					push(&stack, instruction - '0');
				}
				break;
		}

		ip++;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./interpreter <filename>\n");
	}

	FILE *file = fopen(argv[1], "r");
	if (!file) {
		printf("Failed to open the file.\n");
	}

	Program program;
	program.code_length = fread(program.code, sizeof(char), MAX_CODE_LENGTH, file);

	fclose(file);

	execute(&program);

	printf("Press any key to exit...");
	getch(); // Wait for user input

	return 0;
}
