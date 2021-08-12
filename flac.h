#ifndef _FLAC_H_
#define _FLAC_H_
#include <stdint.h>
#include <stdio.h>

typedef struct FlacVorbisComments {
    char *vendor;
    struct CommentKey *keys;
} FlacVorbisComments;

typedef struct CommentKey {
    struct CommentKey *next;
    char *key;
    struct CommentValue *values;
} CommentKey;

typedef struct CommentValue {
    struct CommentValue *next;
    char *value;
} CommentValue;



// Read the start of the FLAC file. Returns 1 if the stream marker is intact.
int flacCheckStreamMarker(FILE *f);

// Reads the next metadata block's header. Returns -1 after all blocks have been consumed, otherwise returns the
// type of the metadata block. nextSeek should start as zero and is used to store seek locations for future blocks.
int flacNextMetadata(FILE *f, long *nextSeek);

// Read all FLAC Metadata Vorbis Comments.
FlacVorbisComments flacReadVorbisComments(FILE *f);

void flacFreeVorbisComments(FlacVorbisComments comments);

#endif