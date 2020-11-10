#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv){
    /* Opens a file and displays the text inside */

    struct stat file_info;
    int file_to_copy;
    int file_copied;
	int result;

	result = stat(argv[1], &file_info);
	char *text_in_file = malloc(file_info.st_size);

    switch(result){

    case -1:
        perror("Can't read the file info");

    default:
        file_to_copy = open(argv[1], O_RDONLY);
        if (file_to_copy == -1){
            perror("Cannot open the file");
        }
        else{
            read(file_to_copy, text_in_file, file_info.st_size);
            close(file_to_copy);
            file_copied = open(argv[2], O_CREAT|O_WRONLY);
            if (file_copied == -1){
                perror("Cannot create a new file");
            }
            else{
                write(file_copied, text_in_file, file_info.st_size);
                close(file_copied);
                free(text_in_file);
            }
        }

    }

}
