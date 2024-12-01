#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *open_file(char *name);

int main(int argc, char **argv)
{
    char *buffer = open_file(argv[1]);

    return 0;
}

char *open_file(char *name)
{
    FILE *file = fopen(name, "r");
    if (!file)
        return NULL;
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    fread(file, size, 1, file);
    buffer[size] = 0;
    fclose(file);
    return buffer;
}
