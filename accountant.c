#include <stdio.h>
#include <string.h>
#include "operations.h"
// this is size of array sent to inserter
int inserterArraySize = 50;

int main(int argc, char *argv[])
{
	int countinue = 1;
	char *exit = "exit";
	char *insert = "insert";
	while (countinue)
	{
		char *line = getLineFromUser();
		// copy that line again because strtok() affect string
		char * lineTokens = malloc(sizeof(char) * 100);
		memcpy (lineTokens, line, strlen(line));
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
			if (*(line + strlen(token) + 1) - 48 <0 || *(line + strlen(token) + 1) - 48 > 9){
				printf("Parameter wrong\n");
				continue;
			}
			// printf("insert13 : %s\n", (line + strlen(token) + 1));
			printf("sum is : %d\n", inserter(line + strlen(token) + 1));
		}
		free(line);
		free(lineTokens);
	}

	// char halwa[7] = {'5', '6', '3', '1', '3', '3', '8'};
	// int add = inserter(halwa, 7);
	// printf("from main %d", add);
	return 0;
}
