/* 
    prime checks or generate prime numbers using external function primechk()
    which is written in x86-64 (AMD64) assembler.

    Copyright (C) 2002-2025 Robert V. <modrobert@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define ERROR 2
#define BASE 10

/* 64bit - C needs one bit (2^64 - 2) */
#define MAX64 18446744073709551614U

int arg_error(char *error);

extern int primechk(long);

int main(int argc, char *argv[])
{
	unsigned long int start = 0;
	unsigned long int stop = 0;
	unsigned long int value = 0;
	int checkonly = FALSE;

	/* need at least one argument, but no more than two */
	if(argc < 2 || argc > 3)
		arg_error("Bad argument(s)\n"); 

	/* check if we are checking one prime only */
	if(!strcmp(argv[1], "-c"))
		checkonly = TRUE;

	/* convert argument to unsigned long int */
	if(checkonly == TRUE)
	{
		if ((start = strtoul(argv[argc - 1], NULL, BASE)) == 0)
			arg_error("Bad integer value\n");
	}
	else if (argc == 2)
	{
		if ((start = strtoul(argv[argc - 1], NULL, BASE)) == 0)
			arg_error("Bad integer value\n");
  		stop = MAX64;
	}
	else if (argc == 3)
	{
	if ((start = strtoul(argv[argc - 2], NULL, BASE)) == 0)
		arg_error("Bad integer value\n");
	if ((stop = strtoul(argv[argc - 1], NULL, BASE)) == 0)
		arg_error("Bad integer value\n");
	}

	/* check if too big for unsigned long int */
	if(start > MAX64 || stop > MAX64) 
		arg_error("The integer value is too large\n"); 

	/* set value to start of range */
	value = start;

	/* the prime check routine */
	if(checkonly == TRUE && primechk(value) == TRUE) 
	{
		printf("%lu is a prime\n", value);
		exit(TRUE);
	}
	else if(checkonly == TRUE) 
	{
		printf("%lu is not a prime\n", value);
		exit(FALSE);
	}
	else
	{
		while(value <= stop)
		{
			if(primechk(value) == TRUE)
				printf("%lu\n", value);
			value++; 
		} 
	}

	return 0;
}

int arg_error(char *error)
{
	fprintf(stderr, "prime v0.64.12\n");
	fprintf(stderr, "==============\n");
	fprintf(stderr, "%s", error);
	fprintf(stderr, "Function: Generate range or check for prime numbers\n");
	fprintf(stderr, "Syntax  : prime [-c] <64bit integer start value> [64bit integer end value]\n");
	fprintf(stderr, "Flag(s) : -c = check only\n");
	fprintf(stderr, "Returns : 0 if no prime, 1 if prime, 2 if error\n");
	exit(ERROR);
}
