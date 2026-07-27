#ifndef _CONFIG_
	#define _CONFIG_

	// Color the cross and some text will be, colors are located in color.h
	#define DETAIL							BCYAN

	// Absolute path to input file, a copy of the Douay Rheims translation is provided in assets
	#define BIBLE_PATH					""

	// Indices for limiting the range of verses, and New Testament index
	#define MIN									195
	#define MAX									138075
	#define NEW_TESTAMENT				108509

	// Cross displayed when fetched. Check cross.h to see the available cross, or create your own!
	#define CROSS 							Latin
	
	#define SPECTRUM_ON 				1

	// Character printed to display terminal colors
	#define COLOR_CHAR					"███"

#endif
