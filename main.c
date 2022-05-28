/*
 * Manix File Fragmenter (MFF)
 * File: main.c
 * Description: main file
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mff.h"

int main(int argc, char *argv[])
{
    printf("MFF [Version 1.0]\n\n");

    if (argc < 3)
    {
        fprintf(stderr, "\nError: at least 3 arguments are necessary!\n\n");
        return 1;
    }

    char const *const file_name = argv[1];

    char const *const action = argv[2];

    if (!strcmp(action, "frag"))
    {
        if (!fexists(file_name))
        {
            fprintf(stderr, "\nError: the file '%s' doesn't exist!\n\n", file_name);
            return 1;
        }

        if (argc < 4)
        {
            fprintf(stderr, "\nError: the size of each fragment was not given.\n\n");
            return 1;
        }

        long frag_size = atol(argv[3]);

        if (!frag_file(file_name, (size_t)frag_size))
        {
            fprintf(stderr, "\nError: failed to fragment file '%s'\n\n", file_name);
            return 1;
        }
    }
    else if (!strcmp(action, "defrag"))
    {
       if (!defrag_file(file_name))
        {
            fprintf(stderr, "\nError: failed to defragment.\n\n", file_name);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "\nError: invalid argument '%s'.\n\n", action);
        return 1;
    }

    return 0;
}