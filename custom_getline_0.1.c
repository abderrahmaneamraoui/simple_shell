#include "shell.h"
char *custom_getline(void)
{
static char buffer[BUFFER_SIZE];
static int buffer_index;
static int bytes_read;

char *line = NULL;
int line_index = 0;
int eof = 0;

while (1)
{
if (buffer_index >= bytes_read)
{
bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
buffer_index = 0;

if (bytes_read == 0)
{
eof = 1;
break;
}
}

char current_char = buffer[buffer_index++];
if (current_char == '\n')
{
line[line_index] = '\0';
break;
}
else
{
line = realloc(line, (line_index + 1) * sizeof(char));
line[line_index++] = current_char;
}
}

if (line == NULL && eof)
return (NULL);

return (line);
}

int main(void)
{
char *line;

while ((line = custom_getline()) != NULL)
{

free(line);
}

return (0);
}
