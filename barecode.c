/* SPDX-License-Identifier: AGPL-3.0-or-later */

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <sys/mman.h>
#endif
#include <stdio.h>
#include <stdlib.h>

struct outbuf {
    void *buf;
    size_t len;
};

static void *allocate(size_t size) {
    void *rv;
#ifdef _WIN32
    if((rv = VirtualAlloc(NULL, size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE)) == NULL) {
        fputs("VirtualAlloc failed\n", stderr); /* TODO print the error */
#else
    if((rv = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
        perror("mmap");
#endif
        exit(1);
    }
    return rv;
}

static void clear_cache(void *buf, size_t size) {
#ifdef _WIN32
    if(!FlushInstructionCache(GetCurrentProcess(), buf, size)) {
        fputs("FlushInstructionCache failed\n", stderr); /* TODO print the error */
        exit(1);
    }
#else
    __builtin___clear_cache(buf, (char *)buf + size);
#endif
}

static void make_executable(void *buf, size_t size) {
#ifdef _WIN32
    DWORD flOldProtect;
    if(!VirtualProtect(buf, size, PAGE_EXECUTE_READ, &flOldProtect)) {
        fputs("VirtualProtect failed\n", stderr); /* TODO print the error */
#else
    if(mprotect(buf, size, PROT_READ|PROT_EXEC)) {
        perror("mprotect");
#endif
        exit(1);
    }
}

static void deallocate(void *buf, size_t size) {
#ifdef _WIN32
    (void)size;
    if(!VirtualFree(buf, 0, MEM_RELEASE)) {
        fputs("VirtualFree failed\n", stderr); /* TODO print the error */
#else
    if(munmap(buf, size)) {
        perror("munmap");
#endif
        exit(1);
    }
}

int main(void) {
    void *ud = NULL;
    for(;;) {
        size_t size;
        if(fread(&size, sizeof size, 1, stdin) != 1) {
            perror("fread");
            return 1;
        }
        if(size == 0) {
            break;
        }
        void *buf = allocate(size);
        if(fread(buf, 1, size, stdin) != size) {
            if(ferror(stdin)) {
                perror("fread");
            } else {
                fputs("Short read\n", stderr);
            }
            return 1;
        }
        clear_cache(buf, size);
        make_executable(buf, size);
        struct outbuf out;
#ifdef _WIN32
        out = ((struct outbuf (*)(FARPROC (WINAPI *)(HMODULE, LPCSTR), HMODULE, void **))buf)(GetProcAddress, GetModuleHandle(__TEXT("Kernel32.dll")), &ud);
#else
        out = ((struct outbuf (*)(void *(*)(void *restrict, const char *restrict), void **))buf)(dlsym, &ud);
#endif
        deallocate(buf, size);
        if(out.len) {
            if(fwrite(out.buf, 1, out.len, stdout) != out.len) {
                perror("fwrite");
                return 1;
            }
        }
        free(out.buf);
    }
}
