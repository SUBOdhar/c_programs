#include <stdbool.h>
#include <string.h>
#include <stdio.h>

char *ext_check(const char *filename)
{
    char *dot = strrchr(filename, '.');
    return dot;
}
int main(int argc, char *argv[]) // argc is the argumnet counter and the argv is the argumnet passed which is an array
{
    FILE *addas;
    FILE *fil; // temp file opener pointer

    if (ext_check(argv[1]) == NULL)
    {
        if (strcmp(argv[1], "create") == 0)
        {
            if (ext_check(argv[2]) == NULL)
            {
                char nasd[25] = "";
                strcat(nasd, argv[2]);
                strcat(nasd, ".drs");
                fil = fopen(nasd, "r"); // opens the argumnet file

                if (fil == NULL)
                {

                    addas = fopen(nasd, "w");
                    fputs("//WELCOME TO DARUS", addas);
                    fclose(addas);
                    printf("%s ", nasd);
                    printf("File created!!");
                }
                else
                {
                    printf("File already exist.");
                }
            }
            else if (strcmp(ext_check(argv[2]), ".drs") == 0)
            {
                fil = fopen(argv[2], "r"); // opens the argumnet file

                if (fil == NULL)
                {
                    addas = fopen(argv[2], "w");
                    fputs("//WELCOME TO DARUS", addas);
                    fclose(addas);
                    printf("%s ", argv[2]);
                    printf("File created!!");
                }
                else
                {
                    printf("File already exist.");
                }
            }
        }
    }
}