#ifndef _VERSE_FETCH_
	#define _VERSE_FETCH_

	#include <stdio.h>
	#include <stdint.h>

	#include "cross.h"

	#define LINE_LENGTH 96


	// Global constant array that will be used to retrieve lines, 
	// book, and testament. Previous iterations would pass in DATA
	// into functions accessing DATA (i.e. retreiveVerseEnd). However
	// it was quite redundant to pass it every time the functions were
	// called.
	const char **DATA;
	
	// This struct helps organize data and makes the code readable
	struct VerseInfo {
		uint32_t verseStart;						// Stores the start of the verse
		uint32_t verseEnd;							// Stores the next blank line from verseIndex
		uint32_t bookIndex;							// Stores the index of the book title
		const char *testament;					// Stores the testament of the verse
	};

	// This function operates similar to Python's FILE.readlines() method
	// in that it takes a file and copies the data into an array of char*s.
	//
	// Previous attempts to access lines within in a file were too slow,
	// especially when retrieving the book of the verse, because
	// the file was open for the entire program. However, with an
	// array accessing the lines become faster and simpler. It also allows
	// the file to close sooner, preventing corruption.
	//
	// Possible improvements:
	// 	* Allow for dynamic lines, as of now every line is the same length.
	// 	  With dynamic line length less memory could be taken up. As of now
	// 	  LINE_LENGTH (defined above) is a constant 96. The minimum to get
	// 	  every character from each line.
	// 	  NOTE: wc -L assets/bible.txt
	//
	// 	  TODO: implement a dynamic length readlines()
	char **readlines(FILE *file, uint32_t start, uint32_t end);

	// Generates a random number between range and checks if it starts with an integer
	uint32_t generate_start(const char **lines, uint32_t min, uint32_t max);

	// Returns next blank line from index
	uint32_t retrieve_verse_end(uint32_t index);
	
	// Returns testament of book/verse
	char *retrieve_testament(uint32_t index);

	// Retrieves name of the book the verse is in
	uint32_t retrieve_book_index(uint32_t index);

	// Helper function for retrieveBook(), checks if all characters are capitalized
	uint32_t check_valid_book_index(const char *line, uint32_t len);

	// Displays cross, verse, book, testament
	void fetch(struct VerseInfo *const verse, struct Cross cross);
	//void fetch(struct VerseInfo verse, struct Cross cross);

	// Displays 2 rows of colors, common within fetching programs
	void display_spectrum(const char *icon);
#endif
