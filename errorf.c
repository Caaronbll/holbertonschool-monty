#include "monty.h"

FILE *file = NULL;

/**
 * errorf - inputs an error
 */

void errorf(void)
{
	fclose(file);
	exit(EXIT_FAILURE);
}
