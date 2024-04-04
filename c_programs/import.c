#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_FILE_PATH_LENGTH 100

// Function to check if a word is "import"
bool isImport(const char *word)
{
    return strcmp(word, "import") == 0;
}

// Function to remove the leading and trailing double quotes and semicolon from a string
void removeQuotesAndSemicolon(char *str)
{
    int len = strlen(str);
    if (len >= 3 && str[0] == '"' && str[len - 2] == '"' && str[len - 1] == ';')
    {
        memmove(str, str + 1, len - 3);
        str[len - 3] = '\0';
    }
}

// Function to get the file paths after the 'import' keyword in a file
char **getImportFilePaths(const char *filename, int *numPaths)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    char line[MAX_FILE_PATH_LENGTH];
    char **paths = NULL;
    *numPaths = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, " \t\n\"");
        while (token != NULL)
        {
            if (isImport(token))
            {
                token = strtok(NULL, " \t\n\"");
                if (token != NULL)
                {
                    removeQuotesAndSemicolon(token);
                    paths = realloc(paths, (*numPaths + 1) * sizeof(char *));
                    if (paths == NULL)
                    {
                        printf("Memory allocation failed.\n");
                        fclose(file);
                        return NULL;
                    }
                    paths[*numPaths] = strdup(token);
                    (*numPaths)++;
                    break;
                }
            }
            token = strtok(NULL, " \t\n\"");
        }
    }

    fclose(file);
    return paths;
}

int main(int argc, char *argv[]) // argc is the argumnet counter and the argv is the argumnet passed which is an array
{

    int numPaths;
    char **paths = getImportFilePaths(argv[1], &numPaths);

    if (paths != NULL)
    {
        printf("Number of file paths after 'import': %d\n", numPaths);
        for (int i = 0; i < numPaths; i++)
        {
            printf("File path %d: %s\n", i + 1, paths[i]);
            free(paths[i]);
        }
        free(paths);
    }

    return 0;
}
