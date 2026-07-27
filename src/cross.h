#ifndef _CROSS_
	#define _CROSS_

	// If you want to create a cross just follow the format and craete a unique name.
	struct Cross {
		const char lines[8][17]; // Format is 8 rows 16 columns
	};
	
	// Latin is a good template to create custom crosses
	struct Cross Latin = {
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
	struct Cross Eastern = {
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
	struct Cross Greek = {
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
	struct Cross Celtic = {
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
	struct Cross Patriarch = {
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
	struct Cross Jerusalem = {
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
