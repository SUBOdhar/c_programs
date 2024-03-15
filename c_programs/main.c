#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

bool ext_check(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot + 1, "darus") == 0);
}

char *tmp_darus()
{
    static char temp_path[MAX_PATH];
    char fld[] = "\\darus\\";
    GetTempPath(MAX_PATH, temp_path);
    strcat(temp_path, fld);
    CreateDirectory(temp_path, NULL);
    return temp_path;
}

int main(int argc, char *argv[])
{
    FILE *fil;

    if (argc < 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    if (!ext_check(argv[1]))
    {
        printf("File extension does not match '.darus'\n");
        return 1;
    }

    fil = fopen(argv[1], "r");
    if (fil == NULL)
    {
        printf("Error: Unable to open file '%s'\n", argv[1]);
        return 1;
    }

    printf("Processing...\n");

    FILE *filePointer;
    FILE *outputFile;
    char initialStr[] = "#include <darus.h>\nint main(){\n";
    char str2[] = "}";
    char dataFromFile[10000];
    char flpth[MAX_PATH] = "";
    strcat(flpth, "runner.c");

    strcat(flpth, tmp_darus());

    filePointer = fopen(argv[1], "r");
    outputFile = fopen(flpth, "w");

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
    fclose(filePointer);

    fputs(str1, outputFile);
    fclose(outputFile);

    free(str1);

    char cmmd[MAX_PATH + 30] = "gcc ";
    strcat(cmmd, "\"");
    strcat(cmmd, flpth);
    strcat(cmmd, "\" -o output");
    int compileStatus = system(cmmd);

    if (compileStatus != 0)
    {
        printf("Error: Compilation failed.\n");
        return 1;
    }
    else
    {
        printf("Compilation successful.\n");
        printf("Compiled file location: temp/output.exe\n");
    }

    fclose(fil);
    return 0;
}
