#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input(char *prompt)
{
    static char output[265]; // Define a static array to hold the input
    printf("%s", prompt);
    fgets(output, 265, stdin);
    // Remove trailing newline character if present
    output[strcspn(output, "\n")] = '\0';
    return output;
}
char *print(char *prompt)
{
    printf("%s", prompt);
}
