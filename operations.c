#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
extern int siz;

int inserter(char *arr)
{
	// write data to file
	FILE *out = fopen("database.txt", "a");
	for (int i = 0; i < siz; i++)
	{
		fprintf(out, "%d\n", *(arr + i) - 48);
	}
	fclose(out);
	// read data from file
	FILE *in = fopen("database.txt", "r");
	int sum = 0;
	char ch = getc(in);
	int character = 0;
	while (ch != EOF)
	{
		if (character % 2 == 0)
		{
			sum += (ch - 48);
		}
		ch = getc(in);
		character++;
	}

	fclose(in);
	return sum;
}
