/**********************************************************************************************
*   easings_results.c
*
*   Test program used to check output values given by the functions in raylib easings.h file.
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2019 Juan Miguel López
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/


#include "easings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>


enum easing_types {
	EASE_LINEAR_NONE,
	EASE_LINEAR_IN,
	EASE_LINEAR_OUT,
	EASE_LINEAR_IN_OUT,
	EASE_SINE_IN,
	EASE_SINE_OUT,
	EASE_SINE_IN_OUT,
	EASE_CIRC_IN,
	EASE_CIRC_OUT,
	EASE_CIRC_IN_OUT,
	EASE_CUBIC_IN,
	EASE_CUBIC_OUT,
	EASE_CUBIC_IN_OUT,
	EASE_QUAD_IN,
	EASE_QUAD_OUT,
	EASE_QUAD_IN_OUT,
	EASE_EXPO_IN,
	EASE_EXPO_OUT,
	EASE_EXPO_IN_OUT,
	EASE_BACK_IN,
	EASE_BACK_OUT,
	EASE_BACK_IN_OUT,
	EASE_BOUNCE_OUT,
	EASE_BOUNCE_IN,
	EASE_BOUNCE_IN_OUT,
	EASE_ELASTIC_IN,
	EASE_ELASTIC_OUT,
	EASE_ELASTIC_IN_OUT,
	NUM_EASING_TYPES,
};

static const struct {
	const char *name;
	float (*func)(float, float, float, float);
} easings[] = {
	[EASE_LINEAR_NONE] = {
		.name = "EaseLinearNone",
		.func = EaseLinearNone,
	},
	[EASE_LINEAR_IN] = {
		.name = "EaseLinearIn",
		.func = EaseLinearIn,
	},
	[EASE_LINEAR_OUT] = {
		.name = "EaseLinearOut",
		.func = EaseLinearOut,
	},
	[EASE_LINEAR_IN_OUT] = {
		.name = "EaseLinearInOut",
		.func = EaseLinearInOut,
	},
	[EASE_SINE_IN] = {
		.name = "EaseSineIn",
		.func = EaseSineIn,
	},
	[EASE_SINE_OUT] = {
		.name = "EaseSineOut",
		.func = EaseSineOut,
	},
	[EASE_SINE_IN_OUT] = {
		.name = "EaseSineInOut",
		.func = EaseSineInOut,
	},
	[EASE_CIRC_IN] = {
		.name = "EaseCircIn",
		.func = EaseCircIn,
	},
	[EASE_CIRC_OUT] = {
		.name = "EaseCircOut",
		.func = EaseCircOut,
	},
	[EASE_CIRC_IN_OUT] = {
		.name = "EaseCircInOut",
		.func = EaseCircInOut,
	},
	[EASE_CUBIC_IN] = {
		.name = "EaseCubicIn",
		.func = EaseCubicIn,
	},
	[EASE_CUBIC_OUT] = {
		.name = "EaseCubicOut",
		.func = EaseCubicOut,
	},
	[EASE_CUBIC_IN_OUT] = {
		.name = "EaseCubicInOut",
		.func = EaseCubicInOut,
	},
	[EASE_QUAD_IN] = {
		.name = "EaseQuadIn",
		.func = EaseQuadIn,
	},
	[EASE_QUAD_OUT] = {
		.name = "EaseQuadOut",
		.func = EaseQuadOut,
	},
	[EASE_QUAD_IN_OUT] = {
		.name = "EaseQuadInOut",
		.func = EaseQuadInOut,
	},
	[EASE_EXPO_IN] = {
		.name = "EaseExpoIn",
		.func = EaseExpoIn,
	},
	[EASE_EXPO_OUT] = {
		.name = "EaseExpoOut",
		.func = EaseExpoOut,
	},
	[EASE_EXPO_IN_OUT] = {
		.name = "EaseExpoInOut",
		.func = EaseExpoInOut,
	},
	[EASE_BACK_IN] = {
		.name = "EaseBackIn",
		.func = EaseBackIn,
	},
	[EASE_BACK_OUT] = {
		.name = "EaseBackOut",
		.func = EaseBackOut,
	},
	[EASE_BACK_IN_OUT] = {
		.name = "EaseBackInOut",
		.func = EaseBackInOut,
	},
	[EASE_BOUNCE_OUT] = {
		.name = "EaseBounceOut",
		.func = EaseBounceOut,
	},
	[EASE_BOUNCE_IN] = {
		.name = "EaseBounceIn",
		.func = EaseBounceIn,
	},
	[EASE_BOUNCE_IN_OUT] = {
		.name = "EaseBounceInOut",
		.func = EaseBounceInOut,
	},
	[EASE_ELASTIC_IN] = {
		.name = "EaseElasticIn",
		.func = EaseElasticIn,
	},
	[EASE_ELASTIC_OUT] = {
		.name = "EaseElasticOut",
		.func = EaseElasticOut,
	},
	[EASE_ELASTIC_IN_OUT] = {
		.name = "EaseElasticInOut",
		.func = EaseElasticInOut,
	},
};


static int get_float_arg(char *argvi, char *arg_prefix, float min, float max,
                         float *arg_var);
static int get_string_arg(char *argvi, char *arg_prefix, char *arg_array,
                          size_t max_len);


#define USAGE_MSG \
	"easings.h test program\n"\
	"  usage: ./easing_results [--help]/[OPTIONS]\n"\
	"    Possible options are:\n"\
	"      --b=<val>: Makes <val> the starting value to interpolate\n"\
	"      --c=<val>: Makes <val> the total change in b that needs to occur\n"\
	"      --d=<val>: Makes <val> the total time the interpolation takes\n"\
	"      --td=<val>: Makes <val> the time unit advanced in each iteration\n"\
	"      --out=<file>: Writes the results to a stream specified by <file>\n"\
	"    <val> must be a floating-point value inside a range defined by the\n"\
	"    program for each option. <file> must be a valid path to a file or\n"\
	"    stream.\n"\
	"  If no values or invalid values are provided, the program will use a\n"\
	"  predefined default for each option. If no <file> is provided, the\n"\
	"  program will output to stdout. If any option is provided more than\n"\
	"  once, only the first occurence will be taken into account.\n"

#define MAX_LIMIT_DIV 10000.0f
#define MIN_B 0.0f
#define MAX_B ((FLT_MAX) / (MAX_LIMIT_DIV))
#define MIN_C 1.0f
#define MAX_C ((FLT_MAX) / (MAX_LIMIT_DIV))
#define MIN_TD 0.1f
#define MAX_TD ((FLT_MAX) / (MAX_LIMIT_DIV))
#define MIN_D 0.2f
#define MAX_D ((FLT_MAX) / (MAX_LIMIT_DIV))

#define DFT_ARG_B 0.0f
#define DFT_ARG_C 60.0f
#define DFT_ARG_D 60.0f
#define DFT_ARG_TD 1.0f


int main(int argc, char *argv[])
{
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, USAGE_MSG);
		return EXIT_SUCCESS;
	}

	fprintf(stderr, "easing_results, easings.h test program\n");

	struct {
		unsigned char b: 1;
		unsigned char c: 1;
		unsigned char d: 1;
		unsigned char td: 1;
		unsigned char out: 1;
	} args_set = {
		.b = 0, .c = 0, .d = 0, .td = 0, .out = 0,
	};

	float arg_b;
	float arg_c;
	float arg_d;
	float arg_td;
	char arg_out[FILENAME_MAX] = {'\0'};

	for (int i = 1; argv[i] != NULL; ++i) {
		if (args_set.b == 0 && strncmp(argv[i], "--b=", strlen("--b=")) == 0) {
			if (get_float_arg(argv[i], "--b=", MIN_B, MAX_B, &arg_b) == 0) {
				args_set.b = 1;
			}
		}
		else
		if (args_set.c == 0 && strncmp(argv[i], "--c=", strlen("--c=")) == 0) {
			if (get_float_arg(argv[i], "--c=", MIN_C, MAX_C, &arg_c) == 0) {
				args_set.c = 1;
			}
		}
		else
		if (args_set.d == 0 && strncmp(argv[i], "--d=", strlen("--d=")) == 0) {
			if (get_float_arg(argv[i], "--d=", MIN_D, MAX_D, &arg_d) == 0) {
				args_set.d = 1;
			}
		}
		else
		if (args_set.td == 0 && strncmp(argv[i], "--td=", strlen("--td=")) == 0)
		{
			if (get_float_arg(argv[i], "--td=", MIN_TD, MAX_TD, &arg_td) == 0) {
				args_set.td = 1;
			}
		}
		else
		if (args_set.out == 0 &&
		    strncmp(argv[i], "--out=", strlen("--out=")) == 0)
		{
			if (get_string_arg(argv[i], "--out=", arg_out, FILENAME_MAX) == 0) {
				args_set.out = 1;
			}
		}
		else
		if (args_set.b == 1 && args_set.c == 1 && args_set.d == 1 &&
		    args_set.td == 1 && args_set.out == 1)
		{
			break;
		}
	}

	if (args_set.b == 0)  arg_b = DFT_ARG_B;
	if (args_set.c == 0)  arg_c = DFT_ARG_C;
	if (args_set.d == 0)  arg_d = DFT_ARG_D;
	if (args_set.td == 0)  arg_td = DFT_ARG_TD;

	fprintf(stderr, "Using args b = %f, c = %f, d = %f, td = %f\n",
	        arg_b, arg_c, arg_d, arg_td);

	FILE *fp;

	if (args_set.out == 0) {
		fp = stdout;
	}
	else {
		fp = fopen(arg_out, "wt");

		if (fp == NULL) {
			fprintf(stderr, "Error opening file %s\n", arg_out);
			return EXIT_FAILURE;
		}

		fprintf(stderr, "Using file %s\n", arg_out);
	}

	long iterations = (arg_d / arg_td) + 1.0f;

	fprintf(stderr, "Doing %ld iterations\n", iterations);

	for (enum easing_types i = 0; i < NUM_EASING_TYPES; ++i) {
		fprintf(fp, "%s:\n", easings[i].name);
		fprintf(fp, "--------\n");

		float t = 0.0f;
		float result;

		for (long j = 0; j < iterations; ++j) {
			result = easings[i].func(t, arg_b, arg_c, arg_d);
			fprintf(fp, "%5ld: %12.6f\n", j, result);
			t += arg_td;
		}

		fprintf(fp, "\n");
	}

	if (args_set.out == 1) {
		fclose(fp);
	}

	return EXIT_SUCCESS;
}

static int get_float_arg(char *argvi, char *arg_prefix, float min, float max,
                         float *arg_var)
{
	float result;
	char *endptr;
	size_t prefix_len = strlen(arg_prefix);

	errno = 0;
	result = strtof(argvi + prefix_len, &endptr);

	if (errno != 0 || endptr == argvi + prefix_len) {
		fprintf(stderr, "Error reading argument %s, using default\n",
		                arg_prefix);
		return 1;
	}

	if (result < min || result > max) {
		fprintf(stderr, "Value read for argument %s is out of range, using default\n",
		                arg_prefix);
		return 2;
	}

	*arg_var = result;

	return 0;
}

static int get_string_arg(char *argvi, char *arg_prefix, char *arg_array,
                          size_t max_len)
{
	size_t prefix_len = strlen(arg_prefix);

	if (prefix_len > max_len - 1) {
		fprintf(stderr, "Prefix length is longer than allowed\n");
		return 1;
	}

	strncpy(arg_array, argvi + prefix_len, max_len - 1);
	arg_array[max_len] = '\0';

	return 0;
}