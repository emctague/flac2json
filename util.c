#include "util.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

// Reusable memory for readLengthString.
char *rlsRead = NULL;
uint32_t rlsLen = 0;

uint32_t bsw(uint32_t num) {
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

uint32_t readUI32(FILE *f) {
    uint32_t value;
    fread((char*)&value, 1, 4, f);
    return value;
}

void makeLowercase(char *c) {
    for (; c && *c; c++) *c = (char)tolower(*c);
}

char *readLengthString(FILE *f) {
    uint32_t len = readUI32(f);

    if ((len + 1) > rlsLen) {
        rlsLen = len + 1;
        rlsRead = realloc(rlsRead, rlsLen);

        if (!rlsRead && rlsLen > 0) {
            perror(EPREFIX "A string in the VORBIS block was too long to read into memory");
            fclose(f);
            abort();
        }
    }

    rlsRead[len] = '\0';
    fread(rlsRead, 1, len, f);
    return rlsRead;
}

void freeLengthString() {
    free(rlsRead);
}

void printj(const char *str, ...) {
    va_list args;
    va_start(args, str);

    for (const char *c = str; c && *c; c++) {
        switch (*c) {
        case '%':
            for (const char *d = va_arg(args, char*); d && *d; d++) {
                if (iscntrl(*d) || *d == '\\' || *d == '\"' || *d == '\'') {
                    printf("\\%03o", *d);
                } else {
                    putchar(*d);
                }
            }; break;
        case '`': putchar('"'); break;
        default: putchar(*c); break;
        }
    }

    va_end(args);
}