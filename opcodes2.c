#include "monty.h"

/**
 * pall - prints all nodes of stack
 * @stack: linked list
 * @line_number: current line
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void)line_number;
	temp = *stack;
	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}
