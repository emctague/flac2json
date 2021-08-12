#include <stdio.h>
#include "util.h"
#include "flac.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, EPREFIX "Usage: %s file.flac\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror(EPREFIX "Cannot open input file");
        return 1;
    }

    if (!flacCheckStreamMarker(f)) {
        fprintf(stderr, EPREFIX "Invalid FLAC file\n");
        return 1;
    }

    int blockType;
    long nextSeek = 0;
    while ((blockType = flacNextMetadata(f, &nextSeek)) >= 0 && blockType != 4);

    if (blockType == 4) {
        FlacVorbisComments comments = flacReadVorbisComments(f);
        printj("{\n\t`hasVorbisBlock`: true,\n\t`vendor`: `%`,\n\t`comments`: {\n", comments.vendor);
        for (CommentKey *key = comments.keys; key; key = key->next) {
            if (key != comments.keys) printf(" ],\n");
            printj("\t\t`%`: [ ", key->key);
            for (CommentValue *val = key->values; val; val = val->next) {
                if (val != key->values) printf(", ");
                printj("`%`", val->value);
            }
        }
        printf(" ]\n\t}\n}\n");
        flacFreeVorbisComments(comments);
    } else {
        printj("{ `hasVorbisBlock`: false }\n");
    }

    freeLengthString();
    fclose(f);
    return 0;
}