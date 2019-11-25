#include <string.h>
#include <stdio.h>
#include "inserter.h"

int inserter(char *arr)
{
	// printf("I am in child : %s\n", arr);
	// write data to file
	FILE *out = fopen("database.txt", "a");
	char s[2] = " ";
	char *token;
	/* get the first token */
	token = strtok(arr, s);
	// walk through other tokens
	while (token != NULL)
	{
		// printf( "%d\n", atoi(token));
		fprintf(out, "%d\n", atoi(token));
		token = strtok(NULL, s);
	}
	fclose(out);
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
	return sum;
}

// int sizeOfString(char *str)
// {
// 	int len = 0;
// 	while (*(str + len) != '\0')
// 	{
// 		len++;
// 	}
// 	return len;
// }

// int temp(char *str)
// {
// 	int sum = 0;
// 	char s[1] = " ";
// 	char *token;
// 	/* get the first token */
// 	token = strtok(str, s);

// 	/* walk through other tokens */
// 	while (token != NULL)
// 	{
// 		printf("thi i token %s\n", token);
// 		// sum += writeAndRead(token);
// 		token = strtok(NULL, s);
// 	}
// 	return sum;
// }

// void print2Darray(char **arrOfwords)
// {
// 	for (int i = 0; i < sizeOfString(arrOfwords); i++)
// 	{
// 		// for (int j = 0; j < sizeOfString(*(arrOfwords + i)); j++)
// 		// {
// 		printf("%s", *(arrOfwords + i));
// 		// }
// 		printf("\n");
// 	}
// }

// char *getLineFromUser()
// {
// 	printf("Accountant >> ");
// 	char *user_input = malloc(sizeof(char) * 100);
// 	fgets(user_input, 100, stdin);
// 	// int len = sizeOfString(user_input);
// 	// printf("Length : %d\n", strlen(user_input));
// 	return user_input;
// }

int main(int argc, char *argv[])
{
	// printf("argc : %d\n", argc);
	// printf("argv : %s\n", argv[0]);
	int sum = inserter(argv[0]);
	printf("This is from sum %d\n", sum);
	return sum;
}