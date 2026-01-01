
#include "repository.h" //brings in the data-structure definitions (File, Commit, Repository) and function prototypes so this .c file knows the types it implements.
#include "file_utils.h" //brings in the prototype for copyFileToRepo() used to copy file contents into the repo/ folder.



//complexity:O(1)
void initRepo(Repository *repo) {//ceates repo folder and sets initial values
    repo->head = repo->tail = NULL;
    repo->total_commits = 0;
    //spawns a shell
    system("mkdir -p repo");//runs a shell command to create a directory named repo (the -p prevents error if it already exists)
    printf("Repository initialized!\n");


}


// Complexity: O(n) in number of files in the list
// helper to copy file node list
//The copy is used when creating a new commit so that each commit has its own file-list
File* copyFiles(File *head) {//function returns a pointer to the head of the newly allocated copied list
    if (!head) return NULL;//f the original list is empty, return NULL
    File *newHead = NULL, *tail = NULL;//newHead will be the head of the new list, tail keeps track of the last node for appending
    while (head) {//iterate over each node in the original list
        File *node = malloc(sizeof(File));//allocate memory for a new File node
        strcpy(node->filename, head->filename);//copy filename string from original node into new node
        node->version = head->version + 1;//ncrement version for the new edit
        node->next = NULL;//initialize the next pointer of the new node

        if (!newHead) newHead = node;
        else tail->next = node;//if new list is empty, set newHead; otherwise append to tail
        tail = node;//move tail to the new last node

        head = head->next;//move to next original node
    }
    return newHead;//return pointer to the new list
}



//Add a file to be tracked in the current (latest) commit node. If there is no current commit node, it creates an initial commit node to hold tracked files
void addFile(Repository *repo, const char *filename) {//adds a file to current commit's file list(linked lsit)
    
    
    //if no commits exist yet, create a first commit node to hold the file(s). 
    //This node is a placeholder head/tail with commit_id = 0 and message "Initial commit"
    
    if (!repo->tail) {
        Commit *first = malloc(sizeof(Commit));
        first->commit_id = 0;
        strcpy(first->message, "Initial commit");
        first->files = NULL;
        first->prev = first->next = NULL;
        repo->head = repo->tail = first;
    }

    File *newFile = malloc(sizeof(File));//create a new file node
    strcpy(newFile->filename, filename);//copy the filename
    newFile->version = 1;//set initial version to
    newFile->next = repo->tail->files;
    repo->tail->files = newFile;

    copyFileToRepo(filename, newFile->version);

    printf("File '%s' added to tracking (v1)\n", filename);
}


//Complexity: O(1) for adding a node.
//Add a file to be tracked in the current (latest) commit node. 
//If there is no current commit node, it creates an initial commit node to hold tracked files
void commitChanges(Repository *repo, const char *message) {//creates a new commit node and links it(linked list)
    Commit *newCommit = malloc(sizeof(Commit));
    newCommit->commit_id = ++repo->total_commits;
    strcpy(newCommit->message, message);
    newCommit->files = copyFiles(repo->tail->files);
    newCommit->prev = repo->tail;
    newCommit->next = NULL;

    if (repo->tail)
        repo->tail->next = newCommit;
    else
        repo->head = newCommit;
    repo->tail = newCommit;

    printf("Commit #%d created: %s\n", newCommit->commit_id, message);
}



/*

copyFileToRepo should check if the file exists; your program printed Error: cannot open source file hello.c

currently addFile will blindly add duplicate filenames if called twice

*/


//Print commit history from newest to oldest.
void showLog(Repository *repo) {//traverses the commit list and prints the ommit history
    Commit *curr = repo->tail;//start at the most recent commit.
    while (curr) {
        printf("Commit #%d: %s\n", curr->commit_id, curr->message);
        curr = curr->prev;//iterate backward through the doubly linked list printing commit_id and message
    }
}

//Move the repository’s tail pointer back to a previous commit, effectively treating that commit as the current state
void revertToCommit(Repository *repo, int commit_id) {//moves back to an older commit
    Commit *curr = repo->head;//start at the oldest commit
    while (curr && curr->commit_id != commit_id)//search forward for the commit with given id.
        curr = curr->next;

    if (!curr) {//if not found, print an error
        printf("Invalid commit ID\n");
        return;
    }

    repo->tail = curr;
    printf("Reverted to commit #%d: %s\n", curr->commit_id, curr->message);
}
