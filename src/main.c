// getpid() is POSIX, not C99
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "lib/optparse99/optparse99.h"
#include "versefetch/versefetch.h"
#include "versefetch/config.h"
#include "versefetch/color.h"

#define VERSEFETCH_VERSION "0.1.0"


static void print_version(void) {
	printf("versefetch " VERSEFETCH_VERSION "\n");
	exit(EXIT_SUCCESS);
}

// Default database location when BIBLE_PATH is not set at compile time:
// $XDG_DATA_HOME/versefetch/bible.tsv, falling back to
// $HOME/.local/share/versefetch/bible.tsv. Returns NULL if neither is set.
static const char *default_bible_path(void) {
	static char buf[4096];
	const char *base;
	int n;

	if(BIBLE_PATH[0] != '\0') {
		return BIBLE_PATH;
	}

	base = getenv("XDG_DATA_HOME");
	if(base != NULL && base[0] == '/') {
		n = snprintf(buf, sizeof(buf), "%s/versefetch/bible.tsv", base);
	} else {
		base = getenv("HOME");
		if(base == NULL || *base == '\0') {
			return NULL;
		}
		n = snprintf(buf, sizeof(buf), "%s/.local/share/versefetch/bible.tsv", base);
	}

	if(n < 0 || (size_t)n >= sizeof(buf)) {
		return NULL;
	}

	return buf;
}

int main(int argc, char **argv) {
	char *bible_opt = NULL;
	char *cross_opt = NULL;
	char *color_opt = NULL;
	int no_spectrum = 0;

	struct optparse_opt options[] = {
		{
			.short_name = 'b',
			.long_name = "bible",
			.arg_name = "PATH",
			.arg_storage = &bible_opt,
			.description = "Verse database to read (overrides $VERSEFETCH_BIBLE)",
		},
		{
			.short_name = 'c',
			.long_name = "cross",
			.arg_name = "NAME",
			.arg_storage = &cross_opt,
			.description = "Cross to draw: latin, eastern, greek, celtic, patriarch, jerusalem",
		},
		{
			.short_name = 'C',
			.long_name = "color",
			.arg_name = "NAME",
			.arg_storage = &color_opt,
			.description = "Color of the cross and labels, e.g. cyan, bred, bwhite",
		},
		{
			.short_name = 'S',
			.long_name = "no-spectrum",
			.flag = &no_spectrum,
			.description = "Don't print the terminal color spectrum",
		},
		{
			.short_name = 'h',
			.long_name = "help",
			.function = optparse_print_help,
			.description = "Show this help and exit",
		},
		{
			.short_name = 'V',
			.long_name = "version",
			.function = print_version,
			.description = "Show the version and exit",
		},
		{ .short_name = END_OF_OPTIONS },
	};

	struct optparse_cmd cmd = {
		.name = "versefetch",
		.about = "Fetch a random Bible verse, drawn beside a cross.",
		.operands = "[BOOK [CHAPTER[:VERSE]]]",
		.description =
			"With no operands any verse may be chosen. A trailing CHAPTER or "
			"CHAPTER:VERSE narrows the pick, e.g. \"psalms\", \"1 kings 3\", "
			"\"john 3:16\".",
		.options = options,
	};

	Style style = {
		.cross = &CROSS,
		.detail = DETAIL,
		.spectrum = SPECTRUM_ON,
	};
	Query q;
	Verse verse;
	char bookbuf[128];
	const char *path;
	FILE *bible;
	int rc;

	optparse_parse(&cmd, &argc, &argv);

	if(cross_opt) {
		style.cross = versefetch_cross_by_name(cross_opt);
		if(style.cross == NULL) {
			fprintf(stderr, "%sERROR%s: unknown cross \"%s\". Choose one of: ", BRED, RESET, cross_opt);
			versefetch_list_crosses(stderr);
			return 1;
		}
	}

	if(color_opt) {
		style.detail = versefetch_color_by_name(color_opt);
		if(style.detail == NULL) {
			fprintf(stderr, "%sERROR%s: unknown color \"%s\". Choose one of: ", BRED, RESET, color_opt);
			versefetch_list_colors(stderr);
			return 1;
		}
	}

	if(no_spectrum) {
		style.spectrum = 0;
	}

	if(versefetch_parse_query(argc, argv, &q, bookbuf, sizeof(bookbuf)) != 0) {
		optparse_fprint_usage(stderr);
		return 1;
	}

	path = bible_opt;

	if(path == NULL || *path == '\0') {
		path = getenv("VERSEFETCH_BIBLE");
	}

	if(path == NULL || *path == '\0') {
		path = default_bible_path();
	}

	if(path == NULL) {
		fprintf(stderr, "%sERROR%s: no verse database found. Pass --bible or set VERSEFETCH_BIBLE.\n", BRED, RESET);
		return 1;
	}

	bible = fopen(path, "r");

	if(bible == NULL) {
		fprintf(stderr, "%sERROR%s: versefetch failed to open %s.\n", BRED, RESET, path);
		return 1;
	}

	srand(time(NULL) ^ getpid());
	rc = versefetch_pick_verse(bible, &q, &verse);
	fclose(bible);

	if(rc != 0) {
		fprintf(stderr, "%sERROR%s: no verse matched.\n", BRED, RESET);
		return 1;
	}

	versefetch_display(&verse, &style);

	if(style.spectrum)
		versefetch_display_spectrum(COLOR_CHAR);

	free(verse.line);
	return 0;
}
