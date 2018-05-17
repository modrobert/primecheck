/* prime.c by modrobert 	                        */
/*                                                  */
/* Check or generate prime numbers using primechk()	*/
/* External function written in AMD64 assembler		*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define ERROR 2
#define BASE 10
#define MAX64 18446744073709551614 /* 64bit - C needs one bit (2^64-2) */

extern int primechk(long);

main(int argc, char *argv[])
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

arg_error(char *error)
/* Writes argument-error-message to stderr. */
{
 fprintf(stderr, "prime v0.64.9\n");
 fprintf(stderr, "=============\n");
 fprintf(stderr, "%s", error);
 fprintf(stderr, "Function: Generate or check for prime numbers\n");
 fprintf(stderr, "Syntax  : prime [-c] <64bit integer value>\n");
 fprintf(stderr, "Flag(s) : -c = check only\n");
 fprintf(stderr, "Returns : 0 if no prime, 1 if prime, 2 if error\n");
 exit(ERROR);
}
