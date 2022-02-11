#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
void reddir(char *, int tabs);
char *filetype(unsigned char type)
{
    char *str;
    switch (type)
    {
    case DT_BLK:
        str = "block device";
        break;
    case DT_CHR:
        str = "character device";
        break;
    case DT_DIR:
        str = "directory";
        break;
    case DT_FIFO:
        str = "named pipe (FIFO)";
        break;
    case DT_LNK:
        str = "symbolic link";
        break;
    case DT_REG:
        str = "regular file";
        break;
    case DT_SOCK:
        str = "UNIX domain socket";
        break;
    case DT_UNKNOWN:
        str = "unknown file type";
        break;
    default:
        str = "UNKNOWN";
    }
    return str;
}
int main(int argc, char **argv)
{
    struct dirent *dirent;
    DIR *parentDir;
    int count = 1;
    if (argc < 2)
    {
        printf("Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }
    parentDir = opendir(argv[1]);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", argv[1]);
        exit(-1);
    }

    else
    {
        reddir(argv[1], 0);
    }
}

void reddir(char *temp, int tabs)
{
    char functemp[100];
    struct dirent *dirent2;
    DIR *parentDir2 = opendir(temp);
    int count = 1;

    while ((dirent2 = readdir(parentDir2)) != NULL)
    {
        if (strcmp(dirent2->d_name, ".") != 0 && strcmp(dirent2->d_name, "..") != 0)
        {
            int i = 0;
            for (i = 0; i < tabs; i++)
            {
                printf("\t");
            }
            printf("[%d] %s (%s)\n", count, dirent2->d_name, filetype(dirent2->d_type));
            if (dirent2->d_type == DT_DIR)
            {
                strcpy(functemp, temp);
                strcat(functemp, "/");
                strcat(functemp, dirent2->d_name);
                tabs++;
                reddir(functemp, tabs);
                tabs--;
            }
        }
    }
    closedir(parentDir2);
}
