#include "insert.h"
#include <dirent.h>

int dbExists(char *tableName)
{
    if (tableName == NULL)
    {
        return 0;
    };
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("Error opening directory");
        return 0;
    }
    printf("tableName %s\n", tableName);
    char *fileName;
    strcpy(fileName, tableName);
    strcat(fileName, ".db");

    while ((entry = readdir(dir)) != NULL)
    {
        if (fnmatch(fileName, entry->d_name, 0) == 0)
        {
            closedir(dir);
            return 1;
        }
    }
    closedir(dir);
    return 0;
}

void insert(InputBuffer *input_buffer, char *tableName){

};