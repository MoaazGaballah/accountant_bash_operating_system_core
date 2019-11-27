#include <stdio.h>
#include <string.h>
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

int isNumber(char *str)
{
	printf("this is strlen(str) : %d\n", strlen(str));
	for (int i = 0; i < strlen(str); i++)
	{
		printf("This is str[i] : %c\n",
		       str[i]);
		if (isdigit(str[i]) == 0)
			return 0;
	}

	return 1;
}

int main(int argc, char *argv[], char **envp)
{
	int countinue = 1;
	char *exit = "exit";
	char *insert = "insert";
	char *calc = "calc";
	while (countinue)
	{
		// get a main line from user
		char *exitTokensLine = getLineFromUser();
		// copy that line again because strtok() affect string
		char *inserterTokensLine = malloc(sizeof(char) * 100);
		memcpy(inserterTokensLine, exitTokensLine, strlen(exitTokensLine));
		// printf("You inserterTokensLine : %s\n", exitTokensLine);
		char *calcTokensLine = malloc(sizeof(char) * 100);
		memcpy(calcTokensLine, exitTokensLine, strlen(exitTokensLine));
		// printf("Your calcTokensLine is : %s\n", calcTokensLine);

		char s[1] = " ";
		char *inserterTokens, *exitTokens, *calcTokens;
		/* get the first token */
		exitTokens = strtok(exitTokensLine, s);
		// this value will be null at end of while
		inserterTokens = exitTokens;
		// this value will be used in calc program
		calcTokens = exitTokens;

		/* walk through other tokens */
		// while (exitTokens != NULL)
		// {
			// printf("token : %s\n", token);
			// printf("exit: %s\n", exit);
			// printf("compare : %d\n", strcasecmp(token, exit));

			// if exit found at any where in a line
			if (strcasecmp(exitTokens, exit) == 0 || strcasecmp(exitTokens, exit) == 10)
			{
				// printf("geldi : %s\n", token);
				countinue = 0;
				break;
			}
		// 	exitTokens = strtok(NULL, s);
		// }
		// printf("inserterTokens : %s\n", inserterTokens);
		// printf("insert: %s\n", insert);
		// printf("compare : %d\n", strcasecmp(inserterTokens, insert));
		// if calc is called regardless letter case
		if (strcasecmp(inserterTokens, insert) == 0 || strcasecmp(inserterTokens, insert) == 10)
		{
			// printf("geldi : %s\n", insert);
			// we substract 48 from char to get the int value of that char
			// only numbers is allowed to this function
			// printf("You inserterTokensLine : %s\n", exitTokensLine);
			if (*(inserterTokensLine + strlen(inserterTokens) + 1) - 48 < 0 || *(inserterTokensLine + strlen(inserterTokens) + 1) - 48 > 9)
			{
				printf("Parameter wrong\n");
				continue;
			}
			// printf("insert13 : %s\n", (inserterTokensLine + strlen(inserterTokens) + 1));
			// inserter.c calling
			// printf("sum is : %d\n", inserter(inserterTokensLine + strlen(inserterTokens) + 1));
			int status;
			int f = fork();
			// printf("this is f from fork : %d \n", f);

			// This is array will sent to inserter function
			char *newargv[1];
			newargv[0] = (inserterTokensLine + strlen(inserterTokens) + 1);
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
				WEXITSTATUS(status);
				// printf("Sum is:  %d\n", WEXITSTATUS(status));
			}
		}
		// printf("calcTokens : %s\n", calcTokens);
		// printf("Calc: %s\n", calc);
		// printf("compare : %d\n", strcasecmp(calcTokens, calc));
		// printf("the rest of calcLine : %s\n", (calcTokensLine + strlen(calcTokens) + 1));
		// if calc is called regardless letter case
		else if (strcasecmp(calcTokens, calc) == 0 || strcasecmp(calcTokens, calc) == 10)
		{
			printf("Your calcTokensLine is : %s\n", calcTokensLine);
			int status;
			int f = fork();

			// This is array will sent to inserter function
			char *newargv[1];
			newargv[0] = (calcTokensLine + strlen(calcTokens) + 1);
			newargv[1] = NULL;
			if (f == 0)
			{

				// these are some controls for input
				char *calcErrorTokens = malloc(sizeof(char) * 100);
				memcpy(calcErrorTokens, calcTokensLine, strlen(calcTokensLine));
				if (*(calcErrorTokens + strlen(calcTokens) + 1) != '-')
				{
					printf("You forget '-'\n");
					continue;
				}
				else if (*(calcErrorTokens + strlen(calcTokens) + 2) <= 113 || *(calcTokensLine + strlen(calcTokens) + 2) >= 116)
				{
					printf("You must enter '-s' for single or '-r' for range\n");
					continue;
				}
				
				// printf("%c\n", *(calcErrorTokens + 8));
				if (isdigit(calcErrorTokens[8]) == 0)
				{
					printf("You must enter the first index\n");
					continue;
				}
				else if(strlen(calcErrorTokens) <= 10 )
				{
					printf("You must enter the second index\n");
					continue;
				}
				
				// int count = 0;
				// while (*(calcErrorTokens + 8 + count) != 32)
				// {
				// 	printf("this is counter : %d\n", count);
				// 	count++;
				// }
				// // to go to next character after space
				// count ++;
				// if (isdigit(calcErrorTokens[8 + count]) == 0)
				// {
				// 	printf("You must enter the second index\n");
				// 	continue;
				// }

				// call calc
				status = execve("calc", newargv, envp);
				perror("execve: execve failed\n");
				free(calcErrorTokens);
			}
			else
			{
				// returned value from fork
				wait(&status);
				printf("Result is:  %d\n", WEXITSTATUS(status));
			}
		}else
		{
			printf("Please enter a valid command !\n");
			continue;
		}
		
		free(inserterTokensLine);
		free(exitTokensLine);
		free(calcTokensLine);
	}

	// char halwa[7] = {'5', '6', '3', '1', '3', '3', '8'};
	// int add = inserter(halwa, 7);
	// printf("from main %d", add);
	return 0;
}
