#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include stdlib.h for system() function

int main()
{
    FILE *filePointer;
    FILE *data;
    char str1[150] = "#include<string.h>"; // Increase the size to accommodate concatenated string
    char dataformfile[100];

    filePointer = fopen("test.dhar", "r");
    data = fopen("temp/runner.c", "w");

    if (filePointer == NULL)
    {
        printf("File failed to open.");
        return 1; // Return error code
    }
    else
    {
        while (fgets(dataformfile, 100, filePointer) != NULL)
        {
            // Concatenate the read line to str1
            strcat(str1, dataformfile);
        }

        // Check if the final string exceeds the size of str1
        if (strlen(str1) >= 150)
        {
            printf("Combined string exceeds maximum size.\n");
            return 1; // Return error code
        }
        else
        {
            printf("%s", str1); // Use %s for string, not %c
        }

        fclose(filePointer);

        printf("\nData successfully read from file.\n");
        printf("The file is now closed.\n");
    }

    if (data == NULL)
    {
        printf("File failed to open.");
        return 1; // Return error code
    }
    else
    {
        // Write str1 to the new file
        fputs(str1, data);

        // Close the new file
        fclose(data);

        // Compile the new file
        int compileStatus = system("gcc temp/runner.c -o temp/output");

        if (compileStatus != 0)
        {
            printf("Compilation failed.\n");
            return 1; // Return error code
        }
    }
    return 0;
}
