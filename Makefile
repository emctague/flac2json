CC=cc
CFLAGS=
LFLAGS=
OBJECTS=main.o util.o flac.o
BINARY=flac2json

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(BINARY)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(BINARY)
