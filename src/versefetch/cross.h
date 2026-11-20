#ifndef VERSEFETCH_CROSS_H
#define VERSEFETCH_CROSS_H

#define CROSS_ROWS	8
#define CROSS_WIDTH	16


// If you want to create a cross just follow the format and craete a unique name.
typedef struct Cross {
	const char lines[8][17]; // Format is 8 rows 16 columns
} Cross;

// Only the cross chosen in config.h is used; keep the rest from tripping -Werror

// Latin is a good template to create custom crosses
static const Cross Latin = {
	.lines = {
		"       __       ",
		"      |  |      ",
		" _____|  |_____ ",
		"|_____    _____|",
		"      |  |      ",
		"      |  |      ",
		"      |  |      ",
		"      |__|      ",
	}
};
static const Cross Eastern = {
	.lines = {
		"     _====_     ",
		"    [_    _]    ",
		" _____|  |_____ ",
		"|_____    _____|",
		"      |  |      ",
		"     [   |      ",
		"      |   ]     ",
		"      |__|      ",
	}
};
static const Cross Greek = {
	.lines = {
		"       __       ",
		"      |  |      ",
		"      |  |      ",
		" _____|  |_____ ",
		"|_____    _____|",
		"      |  |      ",
		"      |  |      ",
		"      |__|      ",
	}
};
static const Cross Celtic = {
	.lines = {
		"       __       ",
		"     _|  |_     ",
		" ___/_|  |_\\___ ",
		"|_____    _____|",
		"    \\_|  |_/    ",
		"      |  |      ",
		"      |  |      ",
		"      |__|      ",
	}
};
static const Cross Patriarch = {
	.lines = {
		"     _====_     ",
		"    [_    _]    ",
		" _____|  |_____ ",
		"|_____    _____|",
		"      |  |      ",
		"      |  |      ",
		"      |  |      ",
		"      |__|      ",
	}
};
static const Cross Jerusalem = {
	.lines = {
		"     ______     ",
		"    |_    _|    ",
		" _ +  |  |  + _ ",
		"| |___|  |___| |",
		"|  ___    ___  |",
		"|_|   |  |   |_|",
		"   + _|  |_ +   ",
		"    |______|    ",
	}
};

#endif
