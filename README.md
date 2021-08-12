#  FLAC2JSON

FLAC2JSON reads the metadata fields from a .FLAC file and outputs them in JSON format.

(FLAC2JSON is *not* associated with the FLAC project.)

### Usage:
`flac2json file.flac`

### Output JSON schema:

   - `hasVorbisBlock`: **bool**                       - true if the file has vorbis metadata
   - `vendor`:         **string** (if hasVorbisBlock) - vorbis / FLAC vendor name
   - `comments`:       **object** (if hasVorbisBlock) - maps vorbis comment keys to array of values
        - `<...some key>`: **array<string>** - array of vorbis comment values for each unique key

### Example Output

#### Successful Output:

```json
{
	"hasVorbisBlock": true,
	"vendor": "reference libFLAC 1.2.1 20070917",
	"comments": {
		"copyright": [ "Copyright (C) 2021 Nooooooooobody" ],
		"author": [ "John Author" ],
		"composer": [ "Phillip De Composer Of De Music" ],
		"lyrics": [ "I know a song that gets on everybody's nerves,\015\012everybody's nerves,\015\012everybody's nerves." ],
		"replaygain_track_gain": [ "-10.10 dB" ],
		"itunesadvisory": [ "1" ],
		"barcode": [ "2030404010" ],
		"isrc": [ "AAAAA2929304" ],
		"publisher": [ "Phil Ublisher" ],
		"bpm": [ "128" ],
		"length": [ "121000" ],
		"date": [ "2021-02-02" ],
		"genre": [ "EDM", "Classical", "Torture" ],
		"disctotal": [ "1" ],
		"discnumber": [ "1" ],
		"tracktotal": [ "1" ],
		"tracknumber": [ "1" ],
		"albumartist": [ "Joe Writer", "Mary 'Featured' McArtist" ],
		"album": [ "This Is An Album" ],
		"artist": [ "Joe Writer", "Mary 'Featured' McArtist", "One-tracks McGee" ],
		"title": [ "Someone Let Us Write a Song" ]
	}
}
```

#### Failure Output (No Metadata):

```json
{ "hasVorbisBlock": false }
```

### License

Licensed under the MIT license - see LICENSE file.

### Reference

For a summary of the OGG Vorbis comment format and suggested field names/values, see:
https://www.xiph.org/vorbis/doc/v-comment.html

For a summary of the FLAC file format, see:
https://xiph.org/flac/format.html