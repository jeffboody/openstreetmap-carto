/*
 * Copyright (c) 2015 Jeff Boody
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define SHIELD_WBORDER 4.0f
#define SHIELD_WIDTH   8.0f
#define SHIELD_WSTEP   1.0f
#define SHIELD_HBORDER 4.0f
#define SHIELD_HEIGHT  15.0f
#define SHIELD_HSTEP   1.0f
#define SHIELD_COUNT   5

typedef struct
{
	const char* type;
	const char* fg;
	const char* bg;
} shield_t;

void export(FILE* f, float width, float height, const char* fg, const char* bg)
{
	fprintf(f, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%%\" height=\"100%%\" viewBox=\"0 0 %f %f\">\n",
	        width + 1.0f, height + 1.0f);
	fprintf(f, "  <rect x=\"0.5\" y=\"0.5\" width=\"%f\" height=\"%f\" rx=\"2\" ry=\"2\" id=\"shield\" style=\"fill:#%s;stroke:#%s;stroke-width:1;\"/>\n",
	        width, height, bg, fg);
	fprintf(f, "</svg>\n");
}

int main(int argc, const char** argv)
{
	int i = 0;
	shield_t shields[SHIELD_COUNT] =
	{
		{ .type="motorway",  .fg="000000", .bg="ffffff" },
		{ .type="primary",   .fg="000000", .bg="ffffff" },
		{ .type="secondary", .fg="000000", .bg="ffffff" },
		{ .type="tertiary",  .fg="000000", .bg="ffffff" },
		{ .type="trunk",     .fg="000000", .bg="ffffff" },
	};
	for(i = 0; i < SHIELD_COUNT; ++i)
	{
		int rows;
		int cols;
		for(cols = 1; cols < 12; ++cols)
		{
			for(rows = 1; rows < 5; ++rows)
			{
				// default shield
				char name[256];
				snprintf(name, 256, "symbols/shields/%s_%ix%i.svg",
				         shields[i].type, cols, rows);
				FILE* f = fopen(name, "w");
				if(f == NULL)
				{
					printf("fopen %s failed", name);
					return EXIT_FAILURE;
				}

				export(f,
				       2.0f*SHIELD_WBORDER + cols*SHIELD_WIDTH,
				       2.0f*SHIELD_HBORDER + rows*SHIELD_HEIGHT,
				       shields[i].fg, shields[i].bg);
				fclose(f);

				// z16 shield
				snprintf(name, 256, "symbols/shields/%s_%ix%i_z16.svg",
				         shields[i].type, cols, rows);
				f = fopen(name, "w");
				if(f == NULL)
				{
					printf("fopen %s failed", name);
					return EXIT_FAILURE;
				}

				export(f,
				       2.0f*SHIELD_WBORDER + cols*(SHIELD_WSTEP + SHIELD_WIDTH),
				       2.0f*SHIELD_HBORDER + rows*(SHIELD_HSTEP + SHIELD_HEIGHT),
				       shields[i].fg, shields[i].bg);
				fclose(f);

				// z18 shield
				snprintf(name, 256, "symbols/shields/%s_%ix%i_z18.svg",
				         shields[i].type, cols, rows);
				f = fopen(name, "w");
				if(f == NULL)
				{
					printf("fopen %s failed", name);
					return EXIT_FAILURE;
				}

				export(f,
				       2.0f*SHIELD_WBORDER + cols*(2.0f*SHIELD_WSTEP + SHIELD_WIDTH),
				       2.0f*SHIELD_HBORDER + rows*(2.0f*SHIELD_HSTEP + SHIELD_HEIGHT),
				       shields[i].fg, shields[i].bg);
				fclose(f);
			}
		}
	}
	return EXIT_SUCCESS;
}
