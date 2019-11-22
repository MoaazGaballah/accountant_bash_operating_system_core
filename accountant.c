#include <stdio.h>
#include <string.h>
#include "operations.h"
// this is size of array sent to inserter
int siz = 6;

int main(int argc, char *argv[])
{
	// setbuf(stdout, NULL);
	// char *arr = degerAtama();
	// printf("You entered : %s\n", arr);
	// arr = terseCeviren(arr);
	// printf("After reversing : %s\n", arr);
	// free(arr);
	// int count = 0, i = 0;
	// printf("please enter 10 elements : ");
	// char *user_input = malloc(sizeof(char) * 10);
	// fgets(user_input, 11, stdin);
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	if (*(user_input + i) == '\0'){
	// 		printf('break');
	// 		break;
	// 	}
			
	// 	printf("%c\n", *(user_input+i) );
	// }
	// free(user_input);

	// // while (1)
	// // {

	// // 	i++;
	// // }
	char halwa [6]= {'5','6','3','1','3','3'};
	int add= inserter(halwa);
	printf("from main %d", add);
	return 0;
}
