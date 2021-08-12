#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>
#include <stdio.h>

#define EPREFIX "FLAC2JSON: "

// Add VALUE to linked-list LIST, assuming each value has a 'next' pointer and LIST can be reassigned
#define LAdd(LIST, VALUE) VALUE->next = LIST; LIST = VALUE;

// Byte swap
uint32_t bsw(uint32_t num);

// Read uint32 from file
uint32_t readUI32(FILE *f);

// Convert string to lowercase in-place
void makeLowercase(char *c);

// Read a string which was prefixed with a 32-bit integer encoding its length.
// This is stored into memory which is overwritten with each call (do not reuse).
char *readLengthString(FILE *f);

// Clean up the string used by readLengthString.
void freeLengthString();

// Print JSON: A special print utility with different format behaviour:
//  - The backtick character ` is substituted for a quote " when printing directly from the format string.
//    This is done for convenience/readability in-editor because escape sequences can be annoying to read.
//  - Upon encountering a percent symbol %, the next string from the variadic arguments is printed with characters
//    which would be invalid in JSON strings escaped.
void printj(const char *str, ...);

#endif