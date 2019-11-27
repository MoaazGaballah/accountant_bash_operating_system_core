#include <string.h>
#include <stdio.h>
#include <ctype.h>

// #define INT_DECIMAL_STRING_SIZE(int_type) ((__CHAR_BIT__ * sizeof(int_type) - 1) * 10 / 33 + 3)

// char *int_to_string_alloc(int x)
// {
//     int i = x;
//     char buf[INT_DECIMAL_STRING_SIZE(int)];
//     char *p = &buf[sizeof buf - 1];
//     *p = '\0';
//     if (i >= 0)
//     {
//         i = -i;
//     }
//     do
//     {
//         p--;
//         *p = (char)('0' - i % 10);
//         i /= 10;
//     } while (i);
//     if (x < 0)
//     {
//         p--;
//         *p = '-';
//     }
//     size_t len = (size_t)(&buf[sizeof buf] - p);
//     char *s = malloc(len);
//     if (s)
//     {
//         memcpy(s, p, len);
//     }
//     return s;
// }

int calc(char *arr)
{
    // printf("I am in child : %s\n", arr);
    // read data from file
    FILE *in = fopen("database.txt", "r");
    int sum = 0;
    char *line = malloc(sizeof(char) * 100);
    char *s = "-s";
    char *r = "-r";
    // this integer to check paramaeters
    int checkParam;

    char space[2] = " ";

    // get the 's' or 'r'
    char *singleOrRangeToken = strtok(arr, space);
    // printf("This is singleOrRangeToken : %s\n", singleOrRangeToken);

    // get the first token
    char *firstIndexToken = strtok(NULL, space);
    // printf("this is firstIndexToken : %s\n", firstIndexToken);
    // printf("this is isNumber(firstIndexToken) : %d\n", isNumber(firstIndexToken));

    // get the second token
    char *secondIndexToken = strtok(NULL, space);

    // this instruction set the last element in secondIndexToken to NULL (0)
    secondIndexToken[strlen(secondIndexToken) - 1] = 0;
    // printf("this is secondIndexToken : %s\n", secondIndexToken);
    // printf("this is strlen(secondIndexToken) : %d\n", strlen(secondIndexToken));
    // printf("this is isNumber(secondIndexToken) : %d\n", isNumber(secondIndexToken ));

    // printf("this is atoi(firstIndexToken) : %d\n", atoi(firstIndexToken));
    // printf("this is atoi(secondIndexToken) : %d\n", atoi(secondIndexToken));

    // if entries are not numbers or second index is lower than the first index or second index is out of bound
    if (strcasecmp(singleOrRangeToken, s) == 0 || strcasecmp(singleOrRangeToken, s) == 10)
    {
        int currentPointer = 0;
        int firstIndexOutOfBound = 1, secondIndexOutOfBound = 1;
        while (fgets(line, 100, in) != NULL)
        {
            // printf("counter is : %d \t", currentPointer);
            // printf("atoi(firstIndexToken) is : %d\t", atoi(firstIndexToken));
            if (currentPointer == atoi(firstIndexToken))
            {
                firstIndexOutOfBound = 0;
                sum += atoi(line);
                // do not add the same index twice
                if (atoi(firstIndexToken) == atoi(secondIndexToken))
                {
                    break;
                }
            }

            // printf("atoi(secondIndexToken) is : %d\n", atoi(secondIndexToken));
            if (currentPointer == atoi(secondIndexToken))
            {
                secondIndexOutOfBound = 0;
                sum += atoi(line);
                // there is no need to read the whole file
                break;
            }
            // printf("sum is : %d\n", sum);
            currentPointer++;
        }

        if (firstIndexOutOfBound == 1)
        {
            // return "First index is out of bound";
            return 101010101011;
        }
        else if (atoi(firstIndexToken) != atoi(secondIndexToken) && secondIndexOutOfBound == 1) // to avoid nested if statement when atoi(firstIndexToken) == atoi(secondIndexToken)
        {
            // return "Second index is out of bound";
            return 101010101010;
        }

        fclose(in);
        free(line);
        // printf("sum befor return is : %d\n", sum);
        return sum;
    }
    else if (strcasecmp(singleOrRangeToken, r) == 0 || strcasecmp(singleOrRangeToken, r) == 10)
    {
        int currentPointer = 0;
        while (fgets(line, 100, in) != NULL)
        {
            // printf("counter is : %d \t", currentPointer);
            // printf("atoi(firstIndexToken) is : %d\t", atoi(firstIndexToken));
            // printf("atoi(secondIndexToken) is : %d\n", atoi(secondIndexToken));
            if (currentPointer >= atoi(firstIndexToken) && currentPointer <= atoi(secondIndexToken))
            {
                sum += atoi(line);
                if (atoi(firstIndexToken) == atoi(secondIndexToken))
                {
                    // there is no need to read the whole file
                    break;
                }
            }

            // printf("sum is : %d\n", sum);
            currentPointer++;
        }
        fclose(in);
        free(line);
        // printf("sum befor return is : %d\n", sum);
        return sum;
    }
    else
    {
        fclose(in);
        free(line);
        // failure
        return 0;
    }
}
int isNumber(char *str)
{
    // printf("this is strlen(str) : %d\n", strlen(str));
    for (int i = 0; i < strlen(str); i++)
    {
        // printf("This is str[i] : %c\n",
        //        str[i]);
        if (isdigit(str[i]) == 0)
            return 0;
    }

    return 1;
}
int main(int argc, char *argv[])
{
    // printf("argc : %d\n", argc);
    // printf("argv : %s\n", argv[0]);
    int sum = calc(argv[0]);
    printf("This is sum from main calc %d\n", sum);

    // int sum = calc(argv[0]);

    // printf("This is from isNumber("") : %d\n", isNumber("1"));
    // printf("This is from isNumber("") : %d\n", isNumber("3"));
    return sum;
}