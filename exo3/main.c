#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv){
    /* Opens a file and displays the text inside */

    struct stat file_info;
    int file_descriptor;
	int result;

	result = stat(argv[1], &file_info);
	char *text_in_file = malloc(file_info.st_size);

    switch(result){

    case -1:
        perror("Cannot read the file info");

    default:

        switch (fork()){
        case -1:
            perror("Cannot create a son process");
            exit(-1);
            break;

        case 0:
            file_descriptor = open(argv[1], O_RDONLY);
            if (file_descriptor == -1){
                perror("Cannot open the file");
            }
            else{
                read(file_descriptor, text_in_file, 10);
                printf("%s \n",text_in_file);
                close(file_descriptor);
                exit(0);
                break;
            }

        default:
            wait(NULL);
            file_descriptor = open(argv[1], O_RDONLY);
            if (file_descriptor == -1){
                perror("Cannot open the file");
            }

            else{
                read(file_descriptor, text_in_file, 5);
                printf("%s \n",text_in_file);
                close(file_descriptor);
                break;
            }

        }
    free(text_in_file);
        }

    }

}
