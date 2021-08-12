#include "flac.h"
#include "util.h"
#include <string.h>
#include <search.h>
#include <stdlib.h>

int flacCheckStreamMarker(FILE *f) {
    char flacMarker[4];
    fread(flacMarker, 1, 4, f);
    return !strncmp(flacMarker, "fLaC", 4);
}

int flacNextMetadata(FILE *f, long *nextSeek) {
    if (*nextSeek < 0) { fseek(f, -*nextSeek, SEEK_SET); return -1; }
    if (*nextSeek != 0) fseek(f, *nextSeek, SEEK_SET);

    uint32_t metaHeader = bsw(readUI32(f));

    uint32_t isLastMetadata = (metaHeader >> 31);
    uint32_t blockType = (metaHeader >> 24) & (0b01111111);
    uint32_t metaLength = metaHeader & 0x00FFFFFF;
    *nextSeek = ftell(f) + metaLength;
    if (isLastMetadata) *nextSeek = -*nextSeek;

    return (int)blockType;
}

FlacVorbisComments flacReadVorbisComments(FILE *f)
{
    ENTRY item;
    ENTRY *found;
    FlacVorbisComments comments;

    comments.vendor = strdup(readLengthString(f));
    comments.keys = NULL;

    // Read all comments into a hashtable
    uint32_t numComments = readUI32(f);
    hcreate(numComments * 2);

    for (int i = 0; i < numComments; i++) {
        // Read comment name and text
        char *comment = readLengthString(f);
        char *name = strtok(comment, "=");
        char *text = strtok(NULL, "=");

        // Create a new comment value
        CommentValue *cVal = malloc(sizeof(CommentValue));
        cVal->next = NULL;
        cVal->value = text ? strdup(text) : NULL;

        // Set up a search table item for it
        item.key = strdup(name);
        item.data = NULL;
        makeLowercase(item.key);

        // Check if the item exists already
        if ((found = hsearch(item, FIND)) != NULL) {
            LAdd(((CommentKey*)found->data)->values, cVal);
            free(item.key);
        } else {
            CommentKey *cKey = malloc(sizeof(CommentKey));
            cKey->key = strdup(item.key);
            cKey->values = cVal;
            LAdd(comments.keys, cKey);

            item.data = cKey;
            hsearch(item, ENTER);
        }
    }

    hdestroy();

    return comments;
}

void flacFreeVorbisComments(FlacVorbisComments comments)
{
    for (CommentKey *iKey = comments.keys; iKey;) {
        CommentKey *key = iKey;
        iKey = key->next;

        for (CommentValue *iVal = key->values; iVal;) {
            CommentValue *val = iVal;
            iVal = iVal->next;

            free(val->value);
            free(val);
        }

        free(key->key);
        free(key);
    }

    free(comments.vendor);
}
