/*
the entry point of the program
Takes user input (init, add, commit, log, revert, etc.
Calls the appropriate repository functions


front-end interface for the version control system
*/

#include  <stdio.h>
#include "repository.h" //acess to repo functions
//" " for your compiler searches current directory first

int main() {
    Repository repo;//declares a variable repo of custom Repository struct (defined in repository.h)
    initRepo(&repo);//initializes the repository: sets pointers (like head/tail) to NULL, sets total_commits = 0, and likely creates the repo/ folder on disk

    char command[50];//creates a fixed-size buffer to store the command the user types (e.g., "add", "commit", etc.)
    while (1) {//infinite loop  which will run until you break)user hits exit)
        printf("\n> ");
        scanf("%s", command);//reads a whitespace-delimited string from stdin into command. It stops at the first whitespace (space/newline)
        
        if (strcmp(command, "add") == 0) {//checks if the entered command equals the string "add". strcmp returns 0 when equal
            char filename[100];//creates a buffer to store the filename the user will type next.
            scanf("%s", filename);//reads the filename(again white space delimiter)
            addFile(&repo, filename);//calls your function to add the file to the repo’s staging (and the implementation likely copies the file into repo/ as filename_v1 etc.)
            //addFile function create File node, set version, call copyFileToRepo(filename, version)
        }

        //this handles the commit
        else if (strcmp(command, "commit") == 0) {
            char message[200];//buffer to hold the commit message (can include spaces).
            getchar(); // clear newline
            fgets(message, sizeof(message), stdin);//reads a whole line (including spaces) into message
            message[strcspn(message, "\n")] = 0;//
            commitChanges(&repo, message);//creates a new commit with the message
        }
        else if (strcmp(command, "log") == 0)//traverses the commit linked list (from tail to head) and prints each commit_id and message
            showLog(&repo);

        else if (strcmp(command, "revert") == 0) {//reads an integer commit id (scanf("%d", &id)), then calls revertToCommit(&repo, id)
            int id;
            scanf("%d", &id);
            revertToCommit(&repo, id);//
        }
        else if (strcmp(command, "exit") == 0)//If command is exit, break exits the infinite loop, program continues to return 0; and ends.
            break;

        else
            printf("Unknown command\n");//For any unrecognized command, prints Unknown command
    }

    return 0;
}
