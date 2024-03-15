#include <stdio.h>
#include <windows.h>
#include <string.h>

int main()
{
    char temp_path[MAX_PATH];
    char fld[100] = "darus\\";
    GetTempPath(MAX_PATH, temp_path);
    strcat(temp_path, fld);
    if (CreateDirectory(temp_path, NULL))
    return 0;
}
