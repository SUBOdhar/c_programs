#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fil;

    // Check if a filename is provided as an argument
    if (argc < 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Check if the file has the correct extension
    const char *dot = strrchr(argv[1], '.');
    if (!(dot && strcmp(dot + 1, "darus") == 0))
    {
        printf("File extension does not match '.darus'\n");
        return 1;
    }

    // Open the file
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

    filePointer = fopen(argv[1], "r");
    outputFile = fopen("temp/runner.c", "w");

    if (filePointer == NULL || outputFile == NULL)
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

    // Compile the outputFile
    int compileStatus = system("gcc temp/runner.c -o temp/output");

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
