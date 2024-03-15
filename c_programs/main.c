#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *filePointer;
    FILE *outputFile;
    char initialStr[] = "#include <darus.h>\nint main(){\n";
    char str2[] = "}";
    char dataFromFile[10000];

    filePointer = fopen("test.dhar", "r");
    outputFile = fopen("temp/runner.c", "w");

    if (filePointer == NULL || outputFile == NULL)
    {
        printf("Error: Unable to open files.\n");
        return 1; // Return error code
    }

    // Get the length of the initial string
    size_t initialStrLen = strlen(initialStr);

    // Determine the length of data to read from the file
    size_t dataLength = 0;
    while (fgets(dataFromFile, 10000, filePointer) != NULL)
    {
        dataLength += strlen(dataFromFile);
    }

    // Calculate the total length needed for str1
    size_t totalLength = initialStrLen + dataLength + strlen(str2) + 1; // +1 for null terminator

    // Dynamically allocate memory for str1
    char *str1 = (char *)malloc(totalLength);
    if (str1 == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1; // Return error code
    }

    // Copy the initial string to str1
    strcpy(str1, initialStr);

    // Reset file pointer to beginning of file
    fseek(filePointer, 0, SEEK_SET);

    // Append dataFromFile to str1
    while (fgets(dataFromFile, 10000, filePointer) != NULL)
    {
        strcat(str1, dataFromFile);
    }

    // Append str2 to str1
    strcat(str1, str2);
    fclose(filePointer);

    // Write str1 to outputFile
    fputs(str1, outputFile);
    fclose(outputFile);

    // Free dynamically allocated memory
    free(str1);

    // Compile the outputFile
    int compileStatus = system("gcc temp/runner.c -o temp/output");

    if (compileStatus != 0)
    {
        printf("Error: Compilation failed.\n");
        return 1; // Return error code
    }
    else
    {
        printf("Compilation successful.\n");
    }

    return 0;
}
