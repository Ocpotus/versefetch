#ifndef VERSEFETCH_H
#define VERSEFETCH_H

#include <stddef.h>
#include <stdio.h>

#include "cross/cross.h"

// One verse, parsed from a line of the TSV file:
//   testament <TAB> book <TAB> chapter <TAB> verse <TAB> text
typedef struct Verse {
	char *line;					// Owns the memory every field below points into
	const char *testament;
	const char *book;
	unsigned int chapter;
	unsigned int verse;
	const char *text;
} Verse;

// What the user asked for on the command line. Zero/NULL means "any".
typedef struct Query {
	const char *book;
	unsigned int chapter;
	unsigned int verse;
} Query;

// How the verse is drawn. Defaults come from config.h.
typedef struct Style {
	const Cross *cross;
	const char *detail;
	int spectrum;
	const char *spectrum_char;
} Style;

// query.c
// Builds a query from operands: [BOOK [CHAPTER[:VERSE]]]
// argv[0] is skipped. Returns 0 on success, -1 on malformed input.
int versefetch_parse_query(int argc, char **argv, Query *q, char *bookbuf, size_t bufsize);

// verse.c
// Picks a random verse matching q. On success the caller frees out->line.
int versefetch_pick_verse(FILE *file, const Query *q, Verse *out);

// display.c
void versefetch_display(const Verse *verse, const Style *style);
void versefetch_display_spectrum(const char *icon);

#endif
