/* 
    prime checks or generate prime numbers using external function primechk()
    which is written in x86-64 (AMD64) assembler.

    Copyright (C) 2002 Robert V. <modrobert@gmail.com>

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
#define MAX64 18446744073709551614U /* 64bit - C needs one bit (2^64-2) */

int arg_error(char *error);

extern int primechk(long);

int main(int argc, char *argv[])
{
 unsigned long int invalue; /* value from commandline */
 unsigned long int value; /* value used in incremental loop */
 int wild;
 int checkonly=FALSE;

/* need at least one argument */
 if(argc < 2) arg_error(""); 

 for(wild=1; wild < argc; wild++)
 {
  if(!strcmp(argv[wild], "-c")) checkonly=TRUE;
 }

/* convert argument to unsigned long int */
 if((invalue = strtoul(argv[wild-1], NULL, BASE)) == 0) 
 {
  arg_error("Bad integer value\n"); 
 }

/* check if too big for unsigned long int */
 if(invalue > MAX64) 
 {
  arg_error("The value is too large\n"); 
 }

 value=invalue; /* start from entered value */

/* the prime check routine */
 if(checkonly == TRUE && primechk(value) == TRUE) 
 {
  printf("%lu is a prime\n", invalue);
  exit(TRUE);
 } 
 else if(checkonly == TRUE) 
 {
  printf("%lu is not a prime\n", invalue);
  exit(FALSE);
 }
 else
 {
  while(value <= MAX64) /* do while within 64bit range */
  {
   if(primechk(value) == TRUE) /* is value a prime? */
   {
    printf("%lu\n", value); /* ok, print it */
   } 
   value++; 
  } 
  exit(FALSE);
 }
}

int arg_error(char *error)
/* Writes argument-error-message to stderr. */
{
 fprintf(stderr, "prime v0.64.10\n");
 fprintf(stderr, "==============\n");
 fprintf(stderr, "%s", error);
 fprintf(stderr, "Function: Generate or check for prime numbers\n");
 fprintf(stderr, "Syntax  : prime [-c] <64bit integer value>\n");
 fprintf(stderr, "Flag(s) : -c = check only\n");
 fprintf(stderr, "Returns : 0 if no prime, 1 if prime, 2 if error\n");
 exit(ERROR);
}
