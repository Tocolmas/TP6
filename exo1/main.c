#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int i;

    for (i = 1; i < argc; ++i) {
        int n;
        char data[1025];

        int fd = open(argv[i], O_RDONLY);

        while ((n = read(fd, data, 1024)) > 0) {
            data[n] = '\0';
            printf(data);
        }

        close(fd);
    }

    return 0;
}
