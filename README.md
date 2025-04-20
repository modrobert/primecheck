I wrote this back in 2002 mainly to learn how to mix assembler with C and to 
play around with prime numbers. Added x86-64 (AMD64) support a few years later.
   
Compile with:
nasm -f elf64 primecheck.asm
gcc -Wpedantic -z noexecstack -o prime prime.c primecheck.o

```
prime v0.64.12
==============
Function: Generate range or check for prime numbers
Syntax  : prime [-c] <64bit integer start value> [64bit integer end value]
Flag(s) : -c = check only
Returns : 0 if no prime, 1 if prime, 2 if error
```

Example usage:
./prime 1 100 
./prime 1 500 | column
./prime -c 2
