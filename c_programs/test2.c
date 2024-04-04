#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define MAX_FILENAME_LENGTH 1000

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
