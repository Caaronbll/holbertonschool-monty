#include "monty.h"

/**
 * push - adds a node to the stack
 * @stack: linked list
 * @line_number: line number
 * Return: void
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newNode;

	newNode = malloc(sizeof(stack_t));

	if (!newNode)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(stack);
		errorf();
	}

	(void)line_number;

	if (*stack)
		(*stack)->prev = newNode;

	newNode->prev = NULL;
	newNode->next = *stack;
	newNode->n = 0;
	*stack = newNode;
}

/**
 * pop - removes first node
 * @stack: linked list
 * @line_number: number of line
 * Return: void
 */

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	temp = *stack;
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		fclose(file);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}

	*stack = temp->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(temp);
}

/**
 * pint - prints the value of the first node
 * @stack: linked list
 * @line_number: number of line
 * Return: void
 */

void pint(stack_t **stack, unsigned int line_number)
{
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		fclose(file);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}
