#include <stdio.h>
#include <string.h>
#include "inserter.h"
#include <sys/wait.h>

// this is size of array sent to inserter
int inserterArraySize = 50;

char *getLineFromUser()
{
	printf("Accountant >> ");
	char *user_input = malloc(sizeof(char) * 100);
	fgets(user_input, 100, stdin);
	// int len = sizeOfString(user_input);
	// printf("Length : %d\n", strlen(user_input));
	return user_input;
}

int main(int argc, char *argv[], char **envp)
{
	int countinue = 1;
	char *exit = "exit";
	char *insert = "insert";
	while (countinue)
	{
		char *line = getLineFromUser();
		// copy that line again because strtok() affect string
		char *lineTokens = malloc(sizeof(char) * 100);
		memcpy(lineTokens, line, strlen(line));
		printf("You entered : %s\n", lineTokens);

		char s[1] = " ";
		char *token, *ex;
		/* get the first token */
		token = strtok(lineTokens, s);
		// this value will be null at end of while
		ex = token;
		/* walk through other tokens */
		while (ex != NULL)
		{
			// printf("token : %s\n", token);
			// printf("exit: %s\n", exit);
			// printf("compare : %d\n", strcasecmp(token, exit));

			// if exit found at any where in a line
			if (strcasecmp(ex, exit) == 0 || strcasecmp(ex, exit) == 10)
			{
				// printf("geldi : %s\n", token);
				countinue = 0;
				break;
			}
			ex = strtok(NULL, s);
		}
		printf("token : %s\n", token);
		printf("insert: %s\n", insert);
		printf("compare : %d\n", strcasecmp(token, insert));
		if (strcasecmp(token, insert) == 0 || strcasecmp(token, insert) == 10)
		{
			// printf("geldi : %s\n", insert);
			if (*(line + strlen(token) + 1) - 48 < 0 || *(line + strlen(token) + 1) - 48 > 9)
			{
				printf("Parameter wrong\n");
				continue;
			}
			// printf("insert13 : %s\n", (line + strlen(token) + 1));
			// inserter.c calling
			// printf("sum is : %d\n", inserter(line + strlen(token) + 1));
			int status;
			int f = fork();
			// printf("this is f from fork : %d \n", f);

			// This is array will sent
			char *newargv[1];
			newargv[0] = (line + strlen(token) + 1);
			newargv[1] = NULL;
			if (f == 0)
			{
				status = execve("inserter", newargv, envp);
				perror("execve: execve failed\n");
			}
			else
			{
				// returned value from fork
				wait(&status);
				printf("Sum is:  %d\n", WEXITSTATUS(status));
			}
		}
		free(line);
		free(lineTokens);
	}

	// char halwa[7] = {'5', '6', '3', '1', '3', '3', '8'};
	// int add = inserter(halwa, 7);
	// printf("from main %d", add);
	return 0;
}
