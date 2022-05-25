#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNKSIZE 4096

int main(void) {
    size_t total_bytes_read = 0;
    char *buf = malloc(CHUNKSIZE);
    if(!buf) {
        perror("malloc");
        return 1;
    }
    for(;;) {
        size_t bytes_read = fread(buf + total_bytes_read, 1, CHUNKSIZE, stdin);
        total_bytes_read += bytes_read;
        if(bytes_read < CHUNKSIZE) {
            if(ferror(stdin)) {
                perror("fread");
                return 1;
            } else {
                break;
            }
        } else {
            if(SIZE_MAX - CHUNKSIZE < total_bytes_read) {
                errno = ENOMEM;
                buf = NULL;
            } else {
                /* if this realloc fails, we're going to exit immediately, so we don't care that the old buf leaks */
                buf = realloc(buf, total_bytes_read + CHUNKSIZE);
            }
            if(!buf) {
                perror("realloc");
                return 1;
            }
        }
    }
    if(fwrite(&total_bytes_read, sizeof total_bytes_read, 1, stdout) != 1) {
        perror("fwrite");
        return 1;
    }
    if(fwrite(buf, 1, total_bytes_read, stdout) != total_bytes_read) {
        perror("fwrite");
        return 1;
    }
}
