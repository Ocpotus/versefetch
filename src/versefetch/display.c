#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "versefetch.h"
#include "config.h"
#include "color.h"


static const struct {
	const char *name;
	const Cross *cross;
} crosses[] = {
	{ "latin",     &Latin },
	{ "eastern",   &Eastern },
	{ "greek",     &Greek },
	{ "celtic",    &Celtic },
	{ "patriarch", &Patriarch },
	{ "jerusalem", &Jerusalem },
};

static const struct {
	const char *name;
	const char *code;
} colors[] = {
	{ "black",   RBLACK },   { "red",     RRED },
	{ "green",   RGREEN },   { "yellow",  RYELLOW },
	{ "blue",    RBLUE },    { "magenta", RMAGENTA },
	{ "cyan",    RCYAN },    { "white",   RWHITE },
	{ "bblack",  BBLACK },   { "bred",    BRED },
	{ "bgreen",  BGREEN },   { "byellow", BYELLOW },
	{ "bblue",   BBLUE },    { "bmagenta", BMAGENTA },
	{ "bcyan",   BCYAN },    { "bwhite",  BWHITE },
};

#define COUNT(a) (sizeof(a) / sizeof((a)[0]))

const Cross *versefetch_cross_by_name(const char *name) {
	for(size_t i = 0; i < COUNT(crosses); i += 1) {
		if(strcasecmp(name, crosses[i].name) == 0)
			return crosses[i].cross;
	}

	return NULL;
}

const char *versefetch_color_by_name(const char *name) {
	for(size_t i = 0; i < COUNT(colors); i += 1) {
		if(strcasecmp(name, colors[i].name) == 0)
			return colors[i].code;
	}

	return NULL;
}

void versefetch_list_crosses(FILE *stream) {
	for(size_t i = 0; i < COUNT(crosses); i += 1)
		fprintf(stream, "%s%s", i ? ", " : "", crosses[i].name);
	fprintf(stream, "\n");
}

void versefetch_list_colors(FILE *stream) {
	for(size_t i = 0; i < COUNT(colors); i += 1)
		fprintf(stream, "%s%s", i ? ", " : "", colors[i].name);
	fprintf(stream, "\n");
}

// Prints the cross row (or blank space once the cross runs out) and a tab
static void cross_row(const Style *style, unsigned row) {
	if(row < CROSS_ROWS) {
		printf("%s%s%s\t", style->detail, style->cross->lines[row], RESET);
	} else {
		printf("%*s\t", CROSS_WIDTH, "");
	}
}

// Width in terminal columns, counting each UTF-8 sequence once
static size_t display_width(const char *s, size_t n) {
	size_t w = 0;
	for(size_t i = 0; i < n; i += 1) {
		if(((unsigned char)s[i] & 0xC0) != 0x80) {
			w += 1;
		}
	}

	return w;
}

void versefetch_display(const Verse *verse, const Style *style) {
	const char *text = verse->text;
	unsigned int row = 0;

	cross_row(style, row++);
	printf("\n");
	cross_row(style, row++);
	printf("%sTestament:%s %s\n", style->detail, RESET,
		strcmp(verse->testament, "NT") == 0 ? "New Testament" : "Old Testament");
	cross_row(style, row++);
	printf("%sBook:%s %s %u:%u\n", style->detail, RESET, verse->book, verse->chapter, verse->verse);
	cross_row(style, row++);
	printf("\n");

	// Greedy word wrap at WRAP_WIDTH columns
	while(*text) {
		const char *end = text, *brk = NULL;

		while(*end && display_width(text, end - text) < WRAP_WIDTH) {
			if(*end == ' ')
				brk = end;
			end += 1;
		}
		if(*end && *end != ' ' && brk) {
			end = brk;
		}

		cross_row(style, row++);
		printf("%.*s\n", (int)(end - text), text);

		text = end;

		while(*text == ' ') {
			text += 1;
		}
	}

	// Finish drawing the cross under short verses
	while(row < CROSS_ROWS) {
		printf("%s%s%s\n", style->detail, style->cross->lines[row++], RESET);
	}

	printf("\n");
}

void versefetch_display_spectrum(const char *icon) {
	// Prints out regular colors
	for(unsigned i = 0; i < 8; i += 1) {
		printf("\033[0;%um%s", 30 + i, icon);
	}

	printf("%s\n", RESET);

	// Prints out bright colors
	for(unsigned i = 0; i < 8; i += 1) {
		printf("\033[1;%um%s", 30 + i, icon);
	}

	printf("%s\n", RESET);
}
