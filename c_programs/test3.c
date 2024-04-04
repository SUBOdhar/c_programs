#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define MAX_FILENAME_LENGTH 1000
#define MAX_FILE_PATH_LENGTH 100

// Function prototypes
char *tmp_darus();
char *get_filename_without_extension(const char *filename);
char *get_extension(const char *filename);
void compile_file(const char *filename);
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename> [create]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "create") == 0)
        {
            if (i + 1 < argc)
            {
                char *filename = argv[i + 1];
                char *extension = get_extension(filename);
                if (extension == NULL || strcmp(extension, ".drs") != 0)
                {
                    char new_filename[MAX_FILENAME_LENGTH];
                    snprintf(new_filename, MAX_FILENAME_LENGTH, "%s.drs", filename);

                    FILE *file = fopen(new_filename, "r");
                    if (file == NULL)
                    {
                        file = fopen(new_filename, "w");
                        if (file != NULL)
                        {
                            fputs("//WELCOME TO DARUS", file);
                            fclose(file);
                            printf("File '%s' created!\n", new_filename);
                        }
                        else
                        {
                            printf("Failed to create file '%s'\n", new_filename);
                        }
                    }
                    else
                    {
                        printf("File '%s' already exists.\n", new_filename);
                        fclose(file);
                    }
                }
            }
        }
        else
        {

            compile_file(argv[i]);
        }
    }

    return 0;
}

char *tmp_darus()
{
    static char temp_path[MAX_PATH];
    char folder[] = "darus";
    GetTempPath(MAX_PATH, temp_path);
    strcat(temp_path, folder);
    CreateDirectory(temp_path, NULL);
    return temp_path;
}

char *get_filename_without_extension(const char *filename)
{
    char *result = strdup(filename);
    if (result != NULL)
    {
        char *dot = strrchr(result, '.');
        if (dot != NULL && dot != result)
        {
            *dot = '\0';
        }
    }
    return result;
}

char *get_extension(const char *filename)
{
    char *dot = strrchr(filename, '.');
    return dot != NULL ? dot : "";
}

void compile_file(const char *filename)
{
    char *file_name_without_ext = get_filename_without_extension(filename);
    if (file_name_without_ext == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    char tmp_file_path[MAX_PATH] = "";
    strcat(tmp_file_path, tmp_darus());
    strcat(tmp_file_path, "\\");
    strcat(tmp_file_path, "runner.c");

    FILE *source_file = fopen(filename, "r");
    FILE *output_file = fopen(tmp_file_path, "w");
    import_Data_adder(filename, tmp_file_path);
    if (source_file == NULL || output_file == NULL)
    {
        printf("Error: Unable to open files.\n");
        free(file_name_without_ext);
        return;
    }

    fprintf(output_file, "#include <darus.h>\nint main() {\n");

    char buffer[10000];
    while (fgets(buffer, sizeof(buffer), source_file) != NULL)
    {
        fputs(buffer, output_file);
    }

    fputs("}", output_file);

    fclose(source_file);
    fclose(output_file);

    char command[MAX_PATH + 30] = "";
    snprintf(command, sizeof(command), "gcc \"%s\" -o \"%s\"", tmp_file_path, file_name_without_ext);

    int compile_status = system(command);
    if (compile_status == 0)
    {
        printf("Compilation successful for file '%s'\n", filename);
    }
    else
    {
        printf("Error: Compilation failed for file '%s'\n", filename);
    }

    free(file_name_without_ext);
}

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
char import_Data_adder(file_imo, tmp_file)
{
    int numPaths;
    char **paths = getImportFilePaths(file_imo, &numPaths);
    FILE *imps;
    FILE *addins;
    if (paths != NULL)
    {
        for (int i = 0; i < numPaths; i++)
        {
            paths[i];
            imps = fopen(paths[i], "r");
            free(paths[i]);
            if (imps == NULL)
            {
                printf("file import doesnot exists %c", paths[i]);
            }
            imps = fopen(file_imo, "w");
            addins = fopen(tmp_file, "w");
            char buffer[10000];
            while (fgets(buffer, sizeof(buffer), imps) != NULL)
            {
                fputs(buffer, addins);
            }
        }
        free(paths);
    }
}