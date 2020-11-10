#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char *argv[]){
    int arg_index = 1;
    int file_descriptor;
    int i;
    char *arguments[1000];

    for (i = 1; i < argc - 1; i++){
    	arguments[i-1] = argv[i];
    }
    arguments[i-1] = NULL;

    file_descriptor = open(argv[argc-1], O_WRONLY|O_CREAT, 0755);
    dup2(file_descriptor,STDOUT_FILENO);

    switch(fork()){

        case -1:
            perror("Cannot create a son process.");
            break;

        case 0:
            execvp(arguments[0], arguments);
            exit(0);
            break;

        default:
            close(file_descriptor);
            wait(NULL);
            break;
    }

    return 0;
}
