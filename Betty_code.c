#include "shell.h"
/**
 * main - Program entry point
 *
 * This function is the entry point for the program. It is called
 * by the system when the program is executed. This function always
 * returns 0 to indicate successful execution.
 *
 * Return: 0 if successful, non-zero otherwise
 */

int main(void)
{
char str[MAX_LEN];

print_hello();

printf("Enter a string: ");
fgets(str, MAX_LEN, stdin);
printf("You entered: %s", str);

return (0);
}
/**
 * print_hello - Prints a greeting message
 *
 * This function prints the string "Hello, World" followed by a
 * newline character to the standard output stream.
 */
void print_hello(void)
{
printf("Hello, World\n");
}
