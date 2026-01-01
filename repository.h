/*
Declares data structures and function prototypes for the repository.
Tells other files what exists (so they can call functions defined in repository.c).


*/
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// for linked list files in a commit singly linked list
typedef struct File {//Defines a struct File and then typedef's it so you can write File instead of struct File
    char filename[100];//fixed-size buffer to store the filename
    int version;//version number for that file
    struct File *next;//pointer to the next node
} File;

// for commit history doubly linked list node
typedef struct Commit {//numeric id for the commit
    int commit_id;
    char message[200];//commit message stored
    File *files;//pointer to the head of the linked list of File nodes belonging to this commit
    struct Commit *prev;
    struct Commit *next;//pointers linking commits in both directions
} Commit;

// to hold the entire repository with head/tail commit pointers
typedef struct Repository {
    Commit *head;//head pointer to the earliest commit, tail pointer to the latest
    Commit *tail;
    int total_commits;//how many commits were created
} Repository;


void initRepo(Repository *repo);
void addFile(Repository *repo, const char *filename);
void commitChanges(Repository *repo, const char *message);
void showLog(Repository *repo);
void revertToCommit(Repository *repo, int commit_id);

#endif
