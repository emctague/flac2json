#  FLAC2JSON

Extract Metadata (METADATA_BLOCK_VORBIS_COMMENT) from a FLAC file and print individual
comments in a JSON string.

(FLAC2JSON is *not* associated with the FLAC project.)

### Usage:
`flac2json file.flac`

### Output JSON schema:

- root object
   - `hasVorbisBlock`: **bool**                       - true if the file has vorbis metadata
   - `vendor`:         **string** (if hasVorbisBlock) - vorbis / FLAC vendor name
   - `comments`:       **object** (if hasVorbisBlock) - maps vorbis comment keys to array of values
        - `<...some key>`: **array<string>** - array of vorbis comment values for each unique key

### License

Licensed under the MIT license - see LICENSE file.

### Reference

For a summary of the OGG Vorbis comment format and suggested field names/values, see:
https://www.xiph.org/vorbis/doc/v-comment.html

For a summary of the FLAC file format, see:
https://xiph.org/flac/format.html