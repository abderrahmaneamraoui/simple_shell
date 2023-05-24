/**
* signal_handler - writes new line plus prompt
* @sig: signal
*/
void signal_handler(int sig)
{
(void) sig;

write(STDERR_FILENO, "\n", 1);
write(STDERR_FILENO, "$ ", 2);
}
/**
* handle_file - parses through list of commands in a file and executes
* @filename: name of file with commands to parse through and execute
*/
void handle_file(char *filename)
{
char *buff = NULL;
char **args = NULL;
char *copyBuff = NULL;
int i, newline_index;

/* read file and write commands to a buff */
buff = do_mem(4096, NULL);
buff = read_textfile(filename);

/* separate commands in file */
newline_index = has_newline(buff);
copyBuff = do_mem(4096, NULL);
while (newline_index)
{
for (i = 0; i < newline_index; i++)
{
copyBuff[i] = buff[i];
}
copyBuff[i] = '\0';
/* tokenize individual commands */
args = _strtok(copyBuff, " ");
/* execute commands */
execute(args);
free_double(args);
copyBuff = _memset(copyBuff, '\0', newline_index);
shiftbuffer(buff, newline_index + 1, 4096);
newline_index = has_newline(buff);
}
do_mem(0, buff);
}

/**
* main_loop - reads STDIN, tokenizes it and executes command
*  @filename: if argv[1] exist takes in filename
*/
void main_loop(char *filename)
{
char *buff = NULL, **args = NULL, *delim = " \n";
int code = 0;
ssize_t lgetline = 0, buffsize = 4096;

if (filename)
handle_file(filename);
else
{
while (1)
{
/* only print a prompt if isatty is true */
if (isatty(STDIN_FILENO))
write(STDERR_FILENO, "$ ", 2);
buff = do_mem(buffsize, NULL);
/* read command, getline and check if it fails */
while ((lgetline = _getline(buff, STDIN_FILENO)) < 0)
{
do_mem(0, buff);
exit_shell(2, "", -1);
}
if (lgetline == 0)/* exit if ctrl- d */
{
if (isatty(STDIN_FILENO))
write(STDERR_FILENO, "\n", 1);
exit_shell(2, "", code);
}
if (buff[lgetline - 1] != '\n') /* if ctrl- d and some text */
{
do_mem(0, buff);
continue;
}
if ((_strcmp(buff, "exit\n")) == 0) /* check for exit command */
exit_shell(2, "", code);
args = _strtok(buff, delim); /* tokenize STDIN */
code = execute(args);
do_mem(0, buff);
free_double(args);
linum(1);
}
}
}
