/*
Handles file reading, writing, and copying.
It’s the only part that interacts directly with files on your computer.

DEALS WITH READING/WRITING ACTUAL FILESON DISK
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyFileToRepo(const char *filename, int version) {
    //filename:he file you want to copy
    //version:version number yo give to the new copy
    //Copies a given file into the repo/ folder with a new name that includes its version

    char src[150], dest[150];
    //Creates two character arrays to hold the source path and destination path strings
    sprintf(src, "%s", filename);
    //Uses sprintf() (string print) to format file paths
    //src becomes "hello.c"
    //dest becomes "repo/hello.c_v1"

    
    sprintf(dest, "repo/%s_v%d", filename, version);
    

    //opens the source file in read mode ("r")
    //If the user had typed add hello.c, this tries to open hello.c from the current folder
    FILE *in = fopen(src, "r");
    if (!in) {
        //Checks if the file actually exists
        //If fopen() fails, in will be NULL
        printf("Error: cannot open source file %s\n", filename);
        return;
    }

    FILE *out = fopen(dest, "w");
    //Opens the destination file in write mode ("w")
    //his creates (or overwrites) the file at the path like repo/hello.c_v1
    if (!out) {
        //Checks if destination creation failed
        //If so, it prints an error and closes the source file safely
        printf("Error: cannot create destination file\n");
        fclose(in);
        return;
    }
    
    //This is the file copy loop
    char c;
    //Reads one character at a time from the source file (fgetc(in))
    //Writes that character to the destination file (fputc(c, out))
    // does till it reached End Of File (EOF)
    while ((c = fgetc(in)) != EOF)
        fputc(c, out);

    fclose(in);
    fclose(out);
}
