#ifdef _WIN32
#include <fcntl.h>
#endif
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNKSIZE 4096

static void binary_stdio(void) {
#ifdef _WIN32
    if(_setmode(_fileno(stdin), _O_BINARY) == -1 || _setmode(_fileno(stdout), _O_BINARY) == -1) {
        perror("_setmode");
#else
    if(!freopen(NULL, "rb", stdin) || !freopen(NULL, "wb", stdout)) {
        perror("freopen");
#endif
        exit(1);
    }
}

int main(void) {
    size_t total_bytes_read = 0;
    char *buf = malloc(CHUNKSIZE);
    if(!buf) {
        perror("malloc");
        return 1;
    }
    binary_stdio();
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
