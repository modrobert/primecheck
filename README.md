I wrote this back in 2002 mainly to learn how to mix assembler with C and to 
play around with prime numbers. Added x86-64 (AMD64) support a few years later.
   
compile with:
    
nasm -f elf64 primecheck.asm
gcc -o prime prime.c primecheck.o
