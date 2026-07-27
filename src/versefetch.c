#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "versefetch.h"
#include "config.h"
#include "color.h"
#include "cross.h"


int main(void) {
	FILE *BIBLE;

	srand(time(NULL));

	// Loads file into constant array
	BIBLE = fopen(BIBLE_PATH, "r");

	if(BIBLE == NULL) {
		fprintf(stderr, "%sERROR%s: versefetch failed to find a Bible.\n", BRED, RESET);
		return 1;
	}

	// Loads file into constant array
	DATA = (const char**) readlines(BIBLE, MIN, MAX);
	fclose(BIBLE);

	if(DATA == NULL) {
		fprintf(stderr, "%sERROR%s: versefetch failed to fetch a verse.\n", BRED, RESET);
		return 1;
	}

	struct VerseInfo verse = {
		.verseStart 	= generate_start				(DATA, MIN, MAX),
		.verseEnd 		= retrieve_verse_end		(verse.verseStart),
		.bookIndex 		= retrieve_book_index		(verse.verseStart),
		.testament 		= retrieve_testament		(verse.verseStart),
	};

	fetch(&verse, CROSS);

	if(SPECTRUM_ON)
		display_spectrum(COLOR_CHAR);
	
	free(DATA);

	return 0;
}

char **readlines(FILE *file, uint32_t start, uint32_t end) {
	char **lines = malloc((end - start) * sizeof(*lines));

	if(lines != NULL) {
		char buff[LINE_LENGTH];
		uint32_t index = 0;

		while(fgets(buff, LINE_LENGTH, file) && index < end) {
			if(index >= start && index < end) {
				uint32_t buffIndex = 0;
				lines[index] = malloc(LINE_LENGTH);

				if(lines[index] == NULL) {
					free(lines);
					goto EXIT;
				}

				do
					lines[index][buffIndex] = buff[buffIndex];
				while(buff[buffIndex++]);
			}
			index++;
		}
	}

EXIT:
	return lines;
}


uint32_t generate_start(const char **lines, uint32_t min, uint32_t max) {
	uint32_t index;

	// Generates a random number until it meets the conditional
	while(1) {
		uint32_t charIndex = 0;

		do
			index = (rand() % (max + 1 - min) + min);
		while(!isdigit(lines[index][0]));

		// Prevents random lines that begin with an integer from being considered a verse
		while(lines[index][charIndex] != '\0' && !isspace(lines[index][charIndex]))
			charIndex++;

		if(lines[index][charIndex - 1] == '.' && strchr(lines[index], ':'))
			break;
	}

	return index;
}

uint32_t retrieve_verse_end(uint32_t index) {
	// Increments from the verse index until a blank line is indexed
	while(index++)
		if(DATA[index][1] == '\n')
			break;

	return index;
}

char *retrieve_testament(uint32_t index) {
	// A simple comparison to determine the testament in which the verse is in
	return ((index > NEW_TESTAMENT) ? "New Testament" : "Old Testament");
}

uint32_t retrieve_book_index(uint32_t index) {
	// Decrements from the verse index and checks if the line meets the requirements
	while(index--)
		if(check_valid_book_index(DATA[index], strlen(DATA[index])))
			return index;

	return 35; // "THE HOLY BIBLE"
}

uint32_t check_valid_book_index(const char *line, uint32_t len) {
	uint32_t ret = 0;
	// This first if statement is quite janky. These conditionals came from testing
	// and were added based on observerd patterns and bugs.
	if(((len >= 3) && (line[len - 3] == '.')) || (len <= 10))
		goto EXIT;

	// Checks for lowercase, numbers, or special characters
	for(uint32_t i = 0; i < len; i++)
		if(islower(line[i]))
			goto EXIT;

	ret = 1;
EXIT:
	return ret;
}

void fetch(struct VerseInfo *const verse, struct Cross cross) {
	printf("%s%s%s\n", 					DETAIL, cross.lines[0], RESET);
	printf("%s%s\tTestament: %s%s\n", 	DETAIL, cross.lines[1], RESET, verse->testament);
	printf("%s%s\tBook: %s%s", 			DETAIL, cross.lines[2], RESET, DATA[verse->bookIndex]);
	printf("%s%s%s\n", 					DETAIL, cross.lines[3], RESET);
	
	// Ensures that real lines of the cross/verse are printed
	for(uint32_t i = 4; i < 8; i++) {
		printf("%s%s%s", DETAIL, cross.lines[i], RESET);
		if(i >= (verse->verseEnd - verse->verseStart))
			printf("\t%s", DATA[verse->verseStart++]);
		else
			printf("\n");
	}
	printf("\n");
}

void display_spectrum(const char *icon) {
	// Prints out regular colors
	for(uint32_t i = 0; i < 8; i++)
		printf("\033[0;%dm%s", (30 + i), icon);
	printf("%s\n", RESET);

	// Prints out bright colors
	for(uint32_t i = 0; i < 8; i++)
		printf("\033[1;%dm%s", (30 + i), icon);
	printf("%s\n", RESET);
}
