#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

struct outbuf {
    char *buf;
    size_t len;
};

int main(void) {
    void *ud;
    for(;;) {
        size_t size;
        if(fread(&size, sizeof size, 1, stdin) != 1) {
            perror("fread");
            return 1;
        }
        if(size == 0) {
            break;
        }
        char *buf = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        if(buf == MAP_FAILED) {
            perror("mmap");
            return 1;
        }
        if(fread(buf, 1, size, stdin) != size) {
            if(ferror(stdin)) {
                perror("fread");
            } else {
                fputs("Short read\n", stderr);
            }
            return 1;
        }
        __builtin___clear_cache(buf, buf + size);
        if(mprotect(buf, size, PROT_READ|PROT_EXEC)) {
            perror("mprotect");
            return 1;
        }
        struct outbuf out = ((struct outbuf (*)(void *(*)(void *restrict, const char *restrict), void **))buf)(dlsym, &ud);
        if(munmap(buf, size)) {
            perror("munmap");
            return 1;
        }
        if(out.len) {
            if(fwrite(out.buf, 1, out.len, stdout) != out.len) {
                perror("fwrite");
                return 1;
            }
        }
        free(out.buf);
    }
}
