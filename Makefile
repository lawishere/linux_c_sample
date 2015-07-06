

CC := gcc
CFLAGS := -g3 -ggdb3 -Os -Wall


all: linux_dir


linux_dir : linux_dir.c
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -Rf linux_dir

