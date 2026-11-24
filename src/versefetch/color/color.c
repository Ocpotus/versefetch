#include <stddef.h>
#include <strings.h>

#include "color.h"


typedef struct ColorMap {
	const char *name;
	Color code;
} ColorMap;

static const ColorMap color_map[] = {
	{
		.name = "black",
		.code = "\033[0;30m"
	},
	{
		.name = "red",
		.code = "\033[0;31m"
	},
	{
		.name = "green",
		.code = "\033[0;32m"
	},
	{
		.name = "yellow",
		.code = "\033[0;33m"
	},
	{
		.name = "blue",
		.code = "\033[0;34m"
	},
	{
		.name = "magenta",
		.code = "\033[0;35m"
	},
	{
		.name = "cyan",
		.code = "\033[0;36m"
	},
	{
		.name = "white",
		.code = "\033[0;37m"
	},
};

static const ColorMap bright_map[] = {
	{
		.name = "bblack",
		.code = "\033[1;30m"
	},
	{
		.name = "bred",
		.code = "\033[1;31m"
	},
	{
		.name = "bgreen",
		.code = "\033[1;32m"
	},
	{
		.name = "byellow",
		.code = "\033[1;33m"
	},
	{
		.name = "bblue",
		.code = "\033[1;34m"
	},
	{
		.name = "bmagenta",
		.code = "\033[1;35m"
	},
	{
		.name = "bcyan",
		.code = "\033[1;36m"
	},
	{
		.name = "bwhite",
		.code = "\033[1;37m"
	},

};

const char *color_get_ansi(const char *name) {
	for(size_t i = 0; i < sizeof(color_map) / sizeof(*color_map); i += 1) {
		if(strcasecmp(name, color_map[i].name) == 0)
			return color_map[i].code;
	}

	return NULL;
}

const char *color_get_bright_ansi(const char *name) {
	for(size_t i = 0; i < sizeof(bright_map) / sizeof(*bright_map); i += 1) {
		if(strcasecmp(name, bright_map[i].name + 1) == 0)
			return bright_map[i].code;
	}

	return NULL;
}
