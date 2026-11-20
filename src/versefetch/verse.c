// getline() is POSIX, not C99
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "versefetch.h"


static int parse_verse(char *line, Verse *v) {
	char *field[5];
	char *p = line;

	for(int i = 0; i < 5; i++) {
		field[i] = p;
		if(i < 4) {
			p = strchr(p, '\t');
			if(p == NULL)
				return -1;
			*p++ = '\0';
		}
	}

	field[4][strcspn(field[4], "\r\n")] = '\0';
	v->line = line;
	v->testament = field[0];
	v->book = field[1];
	v->chapter = strtoul(field[2], NULL, 10);
	v->verse = strtoul(field[3], NULL, 10);
	v->text = field[4];

	return 0;
}

static int matches(const Verse *v, const Query *q) {
	if(q->book && strcasecmp(q->book, v->book) != 0) {
		return 0;
	}

	if(q->chapter && q->chapter != v->chapter) {
		return 0;
	}

	if(q->verse && q->verse != v->verse) {
		return 0;
	}

	return 1;
}

int versefetch_pick_verse(FILE *file, const Query *q, Verse *out) {
	char *line = NULL;
	size_t cap = 0;
	unsigned long seen = 0;
	Verse v;

	out->line = NULL;

	while(getline(&line, &cap, file) != -1) {
		if(parse_verse(line, &v) != 0 || !matches(&v, q))
			continue;

		// Reservoir sampling: keep the n-th match with probability 1/n.
		// The kept verse takes ownership of the buffer, so getline()
		// allocates a fresh one on the next call.
		if((unsigned long)rand() % ++seen == 0) {
			free(out->line);
			*out = v;
			line = NULL;
			cap = 0;
		}
	}

	free(line);

	return out->line ? 0 : -1;
}
