#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "versefetch.h"

// Accepts "3" or "3:16"
static int parse_ref(const char *s, unsigned *chapter, unsigned *verse) {
	char *end;
	unsigned long c, v = 0;

	if(!isdigit((unsigned char)*s))
		return -1;
	c = strtoul(s, &end, 10);
	if(*end == ':') {
		if(!isdigit((unsigned char)end[1]))
			return -1;
		v = strtoul(end + 1, &end, 10);
	}
	if(*end != '\0' || c == 0)
		return -1;

	*chapter = c;
	*verse = v;
	return 0;
}

int versefetch_parse_query(int argc, char **argv, Query *q, char *bookbuf, size_t bufsize) {
	int last = argc - 1;
	size_t len = 0;

	q->book = NULL;
	q->chapter = 0;
	q->verse = 0;

	if(argc < 2) {
		return 0;
	}

	// A trailing "3" or "3:16" is the reference; everything before it is
	// the book name. "1 kings" is a book, so only look at the last argument.
	if(argc > 2 && parse_ref(argv[last], &q->chapter, &q->verse) == 0) {
		last -= 1;
	}

	// Join the remaining arguments with spaces to allow "1 kings" unquoted
	bookbuf[0] = '\0';
	for(int i = 1; i <= last; i += 1) {
		size_t n = strlen(argv[i]);

		if(len + n + 2 > bufsize) {
			return -1;
		}

		if(len) {
			bookbuf[len] = ' ';
			len += 1;
		}

		memcpy(bookbuf + len, argv[i], n + 1);
		len += n;
	}

	q->book = bookbuf;
	return 0;
}
