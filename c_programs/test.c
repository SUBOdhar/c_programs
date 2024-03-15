
#include <stdio.h>
#include <string.h>
// defining main with arguments
int main(int argc, char *argv[])
{
    FILE *fil;
    const char *dot = strrchr(argv[1], '.'); // Find the last occurrence of '.'
    if (dot && strcmp(dot + 1, "darus") == 0)
    {
    fil = fopen(argv[1], "r");
    if (fil == NULL)
     {
            printf("the file doesnot exists\n");
        }
        else
        {
            printf("processing...");
        }
        fclose(fil);
    }
    else
    {
        printf("file extension doesnot match\n");
        printf("%s", argv[1]);
    }

    return 0;
}
