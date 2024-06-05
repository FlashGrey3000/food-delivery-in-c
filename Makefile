CC=gcc
GTK_FLAGS=$(shell pkg-config --cflags --libs gtk4)

all: gtk_example

gtk_example: gtk_example.c
	$(CC) $(GTK_FLAGS) -o gtk_example gtk_example.c

clean:
	rm -f gtk_example
