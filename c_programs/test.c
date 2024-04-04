#include <string.h>
#include <stdio.h>

char *ext_check(const char *filename)//checks whether there is extension or not 
{
    char *dot = strrchr(filename, '.');
    return dot;
}
int main(int argc, char *argv[]) // argc is the argumnet counter and the argv is the argumnet passed which is an array
{
    FILE *addas;//new file creator pointer 
    FILE *fildas; // temp file opener pointer

    if (ext_check(argv[1]) == NULL)
    {
        if (strcmp(argv[1], "create") == 0)// checks the first argument is create or not 
        {
            if (ext_check(argv[2]) == NULL)
            {
                char nasd[25] = "";
                strcat(nasd, argv[2]);
                strcat(nasd, ".drs");
                fildas = fopen(nasd, "r"); // opens the argumnet file

                if (fildas == NULL)//checks file pre exist or not
                {

                    addas = fopen(nasd, "w");
                    fputs("//WELCOME TO DARUS", addas);//writes this into the new file
                    fclose(addas);
                    printf("%s ", nasd);
                    printf("File created!!");//success message
                }
                else
                {
                    printf("File already exist.");//checks and returns file exist or not 
                }
            }
            else if (strcmp(ext_check(argv[2]), ".drs") == 0)//checks whether the file has extension .drs nor not
            {
                fildas = fopen(argv[2], "r"); // opens the argumnet file

                if (fildas == NULL)
                {
                    addas = fopen(argv[2], "w");
                    fputs("//WELCOME TO DARUS", addas);//writes this into new file
                    fclose(addas);
                    printf("%s ", argv[2]);//prints file name 
                    printf("File created!!");//success message
                }
                else
                {
                    printf("File already exist.");
                }
            }
        }
    }
}