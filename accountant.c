#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
	char *readall = "readall";
	char *clear = "clear";
	char *help = "help";

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
		char *calcErrorTokens = malloc(sizeof(char) * 100);
		memcpy(calcErrorTokens, calcTokensLine, strlen(calcTokensLine));

		char s[1] = " ";
		char *inserterTokens, *exitToken, *calcTokens, *readallToken, *clearToken, *helpToken;
		/* get the first token */
		exitToken = strtok(exitTokensLine, s);
		// this value will be null at end of while
		inserterTokens = exitToken;
		// this value will be used in calc program
		calcTokens = exitToken;
		// this value will be used in readall command
		readallToken = exitToken;
		// this will be used for clear command
		clearToken = exitToken;
		// this variable will be used in help command
		helpToken = exitToken;


		/* walk through other tokens */
		// while (exitTokens != NULL)
		// {
		// printf("token : %s\n", token);
		// printf("exit: %s\n", exit);
		// printf("compare : %d\n", strcasecmp(token, exit));

		// if exit found at any where in a line
		if (strcasecmp(exitToken, exit) == 0 || strcasecmp(exitToken, exit) == 10)
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

			// This is array will sent to inserter program
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
			// printf("Your calcTokensLine is : %s\n", calcTokensLine);
			int status;
			int f = fork();

			// This is array will sent to calc program
			char *newargv[1];
			newargv[0] = (calcTokensLine + strlen(calcTokens) + 1);
			newargv[1] = NULL;
			if (f == 0)
			{

				// these are some controls for input
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
					printf("You must enter the first index valid\n");
					continue;
				}

				int i = 0;

				//Find first space
				while (calcErrorTokens[8 + i] != ' ')
				{
					i++;
				}
				// printf("this is calcErrorTokens[8 + %d] : %c\n", i, calcErrorTokens[8 + i]);
				if (isdigit(calcErrorTokens[8 + i + 1]) == 0)
				{
					printf("You must enter the second index valid\n");
					continue;
				}

				// call calc
				status = execve("calc", newargv, envp);
				perror("execve: execve failed\n");
				// printf("I am here");
				free(calcErrorTokens);
				continue;
			}
			else
			{
				// returned value from fork
				wait(&status);
				printf("Result is:  %d\n", WEXITSTATUS(status));
				free(calcErrorTokens);
			}
		}
		else if (strcasecmp(readallToken, readall) == 0 || strcasecmp(readallToken, readall) == 10)
		{
			// read data from file
			FILE *in = fopen("database.txt", "r");
			int sum = 0;
			char *line = malloc(sizeof(char) * 100);
			while (fgets(line, 100, in) != NULL)
			{
				sum += atoi(line);
				printf("%d\n", atoi(line));
			}
			fclose(in);
			free(line);
		}
		else if (strcasecmp(clearToken, clear) == 0 || strcasecmp(clearToken, clear) == 10)
		{
			const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
			write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		}else if (strcasecmp(helpToken, help) == 0 || strcasecmp(helpToken, help) == 10)
		{
			printf("* You can insert positive numbers to database.txt by calling insert\n");
			printf("        Exmaple : ");
			printf("insert 4 6 9\n");
			printf("* You can add all numbers in range exist in database.txt by calling calc\n");
			printf("        Exmaple : ");
			printf("calc -r 6 9\n");
			printf("Or just numbers in specified indices exist in database.txt by calling calc\n");
			printf("        Exmaple : ");
			printf("calc -s 6 9\n");
			printf("* You can clear console by calling clears\n");
			printf("* You can get available commands by calling help\n");
		}
		else
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
