#include <stddef.h>
#include <string.h>

#include "cross.h"


typedef struct CrossMap {
	const char *name;
	const Cross cross;
} CrossMap;

static const CrossMap map[] = {
	{
		.name = "latin",
		.cross = {
			"       __       ",
			"      |  |      ",
			" _____|  |_____ ",
			"|_____    _____|",
			"      |  |      ",
			"      |  |      ",
			"      |  |      ",
			"      |__|      ",
		},
	},
	{
		.name = "eastern",
		.cross = {
			"     _====_     ",
			"    [_    _]    ",
			" _____|  |_____ ",
			"|_____    _____|",
			"      |  |      ",
			"     [   |      ",
			"      |   ]     ",
			"      |__|      ",
		},
	},
	{
		.name = "greek",
		.cross = {
			"       __       ",
			"      |  |      ",
			"      |  |      ",
			" _____|  |_____ ",
			"|_____    _____|",
			"      |  |      ",
			"      |  |      ",
			"      |__|      ",
		},
	},
	{
		.name = "celtic",
		.cross = {
			"       __       ",
			"     _|  |_     ",
			" ___/_|  |_\\___ ",
			"|_____    _____|",
			"    \\_|  |_/    ",
			"      |  |      ",
			"      |  |      ",
			"      |__|      ",
		},
	},
	{
		.name = "patriarch",
		.cross = {
			"     _====_     ",
			"    [_    _]    ",
			" _____|  |_____ ",
			"|_____    _____|",
			"      |  |      ",
			"      |  |      ",
			"      |  |      ",
			"      |__|      ",
		},
	},
	{
		.name = "jerusalem",
		.cross = {
			"     ______     ",
			"    |_    _|    ",
			" _ +  |  |  + _ ",
			"| |___|  |___| |",
			"|  ___    ___  |",
			"|_|   |  |   |_|",
			"   + _|  |_ +   ",
			"    |______|    ",
		},
	},
};

const Cross *versefetch_cross_by_name(const char *name) {
	for(unsigned long int i = 0; i < sizeof(map) / sizeof(*map); i += 1) {
		if(strcmp(name, map[i].name) == 0) {
			return &map[i].cross;
		}
	}

	return NULL;
}
