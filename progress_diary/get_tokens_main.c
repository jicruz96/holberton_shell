#include "shell.h"

/**
 * main = test file for tokenize function
 * Return: 0
 **/
int main(void)
{
    char **args;
    int i;

    /* while stdin keeps returning tokens, print them */
    while ((args = get_tokens(0)))
    {
        i = 1;
        printf("you submitted the following tokens: \n");
        while (args && *args)
            printf("\t%d.\t%s\n", i++, *(args++));
    }
    
    return (0);
}
