#include "monty.h"

FILE *file = NULL;

/**
 * main - monty bytecode interpreter
 * @argc: argument count
 * @argv: argument array
 * Return: 0 or 1
 */

int main(int argc, char **argv)
{
	void (*f)(stack_t **, unsigned int) = NULL;
	char *buffer = NULL, op[50] = {"\0"}, pushNum[50] = {"\0"}, *token = NULL;
	size_t bufsize = 0;
	stack_t *stack = NULL;
	unsigned int line_number = 1;

	if (argc != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);
	file = fopen(argv[1], "r");
	if (!file)
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);
	for (; getline(&buffer, &bufsize, file) != EOF; line_number++)
	{
		token = strtok((buffer), " \t\n");
		if (!token)
		{
			free(buffer), buffer = NULL;
			 continue;
		}
		strcpy(op, token);
		f = get_f(&stack, line_number, op);
		if (!f)
			fprintf(stderr, "Error: malloc failed\n"), errorf();
		if (strcmp(op, "push") == 0)
		{
			token = strtok(NULL, " \t\n");
			if (!token)
			{
				free(buffer), buffer = NULL, free_stack(&stack);
				fprintf(stderr, "L%d: Usage: Push integer\n", line_number), errorf();
			}
			strcpy(pushNum, token);
		}
		free(buffer), buffer = NULL;
		f(&stack, line_number);
		if (strcmp(op, "push") == 0)
			pushOp(&stack, line_number, pushNum);
	}
	free(buffer), fclose(file), free_stack(&stack);
	return (EXIT_SUCCESS);
}

/**
 * get_f - finds the function to use for the string
 * @stack: stack to operate on
 * @l: line number
 * @code: string used for the function
 * Return: pointer to the right function
 */
void (*get_f(stack_t **stack, int l, char *code))(stack_t **, unsigned int)
{
	instruction_t instruction[] = {
		{"push", push},
		/*{"pall", pall},*/
		{"pint", pint},
		{"pop", pop}
		/*{"swap", swap},*/
		/*{"add", add},*/
		/*{"nop", nop}*/
	};
	int i = 0;

	while (strcmp(code, instruction[i].opcode) != 0)
	{
		i++;
		if (i > 7)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", l, code);
			free_stack(stack);
			errorf();
		}
	}
	return (instruction[i].f);
}

/**
 * pushOp - push operation that sets new value for new node
 * @stack: linked list stack
 * @line_number: current line
 * @pushNum: number to add
 */
void pushOp(stack_t ** stack, unsigned int line_number, char *pushNum)
{
	if(strcmp(pushNum, "0") == 0)
		(*stack)->n = 0;
	if (strcmp(pushNum, "0") != 0)
	{
		(*stack)->n = atoi(pushNum);

		if ((*stack)->n == 0 || (pushNum[0] != '-' && (*stack)->n == -1))
		{
			fprintf(stderr, "Error: L%d: usage: push integer\n", line_number);
			free_stack(stack);
			errorf();
		}
	}
}

/**
 * free_stack - frees a linked list
 * @stack: linked list
 * Return: void
 */

void free_stack(stack_t **stack)
{
	if (!(stack) || !(*stack))
	{
		return;
	}
	free_stack(&((*stack)->next));
	free(*stack);
	*stack = NULL;
}
