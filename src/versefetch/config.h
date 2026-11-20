#ifndef VERSEFETCH_CONFIG_H
#define VERSEFETCH_CONFIG_H

// Color the cross and some text will be, colors are located in color.h
#define DETAIL							BCYAN

// Path to the verse database (one verse per line, tab separated).
// Leave empty to use $XDG_DATA_HOME/versefetch/bible.tsv (or
// ~/.local/share/versefetch/bible.tsv), where install.sh puts it.
// Overridden at runtime by --bible or the VERSEFETCH_BIBLE environment variable.
#ifndef BIBLE_PATH
#define BIBLE_PATH					""
#endif

// Cross displayed when fetched. Check cross.h to see the available cross, or create your own!
#define CROSS 							Latin

// Maximum width of a line of verse text before it wraps
#define WRAP_WIDTH					64

#define SPECTRUM_ON 				1

// Character printed to display terminal colors
#define COLOR_CHAR					"███"

#endif
