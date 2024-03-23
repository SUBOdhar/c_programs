
//  ██████╗░░█████╗░██████╗░██╗░░░██╗░██████╗
//  ██╔══██╗██╔══██╗██╔══██╗██║░░░██║██╔════╝
//  ██║░░██║███████║██████╔╝██║░░░██║╚█████╗░
//  ██║░░██║██╔══██║██╔══██╗██║░░░██║░╚═══██╗
//  ██████╔╝██║░░██║██║░░██║╚██████╔╝██████╔╝
//  ╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚═════╝░╚═════╝░
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

    // Gets the file name from the the file path argument
    char *
    get_flnm(const char *filename)
{
    char *result = strdup(filename); // Make a copy of the filename
    if (result == NULL)
    {
        // Memory allocation failed
        return NULL;
    }

    char *dot = strrchr(result, '.'); // Find last occurrence of '.'
    if (dot && dot != result)
    {                // Ensure dot exists and is not the first character
        *dot = '\0'; // Replace dot with null character
    }

    return result;
}

// Checks the the file argument extension as .darsu or not

bool ext_check(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot + 1, "darus") == 0);
}

// Get the TEMP directory of the system and creates a folder named darus for temporary data storage

char *tmp_darus()
{
    static char temp_path[MAX_PATH];
    char fld[] = "darus";             // folder name
    GetTempPath(MAX_PATH, temp_path); // gets the temp path of the system
    strcat(temp_path, fld);           // combines the tempath and the folder name
    CreateDirectory(temp_path, NULL); // create the folder in the temp dir if not exists
    return temp_path;                 // returns the temp darus folder path
}

// Main function which gets the argument and only first argument is only readed and it will check whether the file exist and is not null

int main(int argc, char *argv[]) // argc is the argumnet counter and the argv is the argumnet passed which is an array
{

    FILE *fil;    // temp file opener pointer
    if (argc < 2) // argumnet checker if the argument is less than 2
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    if (!ext_check(argv[1]))
    {
        printf("File extension does not match '.darus'\n");
        return 1;
    }

    fil = fopen(argv[1], "r"); // opens the argumnet file
    if (fil == NULL)           // checks whether the gigen argument file exists
    {
        printf("Error: Unable to open file '%s'\n", argv[1]);
        return 1;
    }

    printf("Processing %s ...\n", argv[1]); // some processing output
    char *flnm = get_flnm(argv[1]);         // getting the fiel name of the argument file

    FILE *filePointer;
    FILE *outputFile;
    char initialStr[] = "#include <darus.h>\nint main(){\n"; // different header file which contain fifferent function for data processing
    char str2[] = "}";
    char dataFromFile[10000];
    char flpth[MAX_PATH] = "";

    strcat(flpth, tmp_darus()); // gets the Temp file path from the function and combines with the empty flpth char
    strcat(flpth, "\\");        // adds a \ between the file path and file name
    strcat(flpth, "runner.c");  // combines the file name with the file path

    filePointer = fopen(argv[1], "r"); // Opens the .darus file and reads it
    outputFile = fopen(flpth, "w");    // opens the output file which is stored in temporary folder and writes the modified data from .darus file

    if (filePointer == NULL)
    {
        printf("Error: Unable to open files.\n");
        return 1;
    }

    size_t initialStrLen = strlen(initialStr);
    size_t dataLength = 0;

    while (fgets(dataFromFile, 10000, filePointer) != NULL)
    {
        dataLength += strlen(dataFromFile);
    }

    size_t totalLength = initialStrLen + dataLength + strlen(str2) + 1;
    char *str1 = (char *)malloc(totalLength);

    if (str1 == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    strcpy(str1, initialStr);
    fseek(filePointer, 0, SEEK_SET);

    while (fgets(dataFromFile, 10000, filePointer) != NULL)
    {
        strcat(str1, dataFromFile);
    }

    strcat(str1, str2);
    // closes the .darus file
    fclose(filePointer);
    // writes the modified code in the temporary file for compilation
    fputs(str1, outputFile);
    // closes the TEMP file
    fclose(outputFile);
    // frees the str1
    free(str1);

    // creates a command for the system to run
    char cmmd[MAX_PATH + 30] = "gcc ";
    strcat(cmmd, "\"");
    strcat(cmmd, flpth);
    strcat(cmmd, "\" -o ");
    strcat(cmmd, flnm);

    int compileStatus = system(cmmd);
    if (compileStatus != 0)
    {
        printf("Error: Compilation failed.\n");
        return 1;
    }
    else
    {
        printf("Compilation successful.\n");
    }

    fclose(fil);
    return 0;
}
