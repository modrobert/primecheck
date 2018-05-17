; primecheck.asm v0.64.9 
; By modrobert <modrobert@gmail.com> 
; 
; primechk(unsigned long int) returns 1 if input (rax) is a prime,
; otherwise 0; 
; 
; 386 opcodes with 64bit registers for AMD64 (and Intel)
; 
;
; Optimization log: 
;
; 2002-02-19: All primes except 2 always have bit 0 set, always an odd value.
;
; 2002-02-19: No need to check multiples higher than square root of input.
;
; 2002-02-23: Square root is done quicker by using "multiply by self" inside 
;             primeloop instead of fsqrt before loop.
;
; 2002-02-23: Check for low primes before primeloop, not within.
;
; 2002-05-11: "add rbx,0x2" is faster than "inc rbx" two times, one clock
;              cycle saved. ;)
;
;
; For reference:
;
; 64-bit Linux fastcall convention
;    ints/longs/ptrs: RDI, RSI, RDX, RCX, R8, R9
;     floats/doubles: XMM0 to XMM7
;
; The first six integer arguments (from the left) are passed in
; RDI, RSI, RDX, RCX, R8, and R9, in that order. 
; Additional integer arguments are passed on the stack. 
; These registers, plus RAX, R10 and R11 are destroyed by function calls,
; and thus are available for use by the function without saving. 


		BITS 64
		GLOBAL primechk
		SECTION .text

primechk:
		mov r9,rbx		;save rbx since we use it
		mov rcx,rax		;get our 64bit "prime suspect" ;)

; Eliminate low primes first, since square root rounded up don't work when 
; rax is less or equal to 5. Also save some important clocks in primeloop.

		cmp rcx,0x1		
		je noprime
		cmp rcx,0x2
		je prime
		cmp rcx,0x3
		je prime
		cmp rcx,0x4
		je noprime
		cmp rcx,0x5
		je prime

; Primes greater than 2 are always odd.

                bt rcx,0                ;check for bit 0 (0-63)
                jnc noprime             ;not set? not odd, no prime, exit

	
; Now eliminate numbers that aren't primes by dividing with all odd multiples 
; up to square root of input (rax).

initprime:
		mov rbx,0x3		;start with division by 3.

primeloop:
		mov rax,rbx		;move current divisor to multiplicand
		mul rbx			;multiply by self
		jo prime		;if overflow is set, we got a prime
		cmp rax,rcx 		;check result > square root?
		ja prime		;ok, we got a prime 
		cmp rbx,rcx		;we finished dividing?
		jae prime               ;yes, we got a prime
		mov rax,rcx             ;preparing for divide
		mov rdx,0x0		;clearing the high word dividend
		div rbx			;divide
		cmp rdx,0x0		;check if remainder equals 0
		je noprime		;if so no prime
		add rbx,0x2		;add 2, no need to check even digits
		jmp primeloop

noprime:
		mov rax,0x0		;return 0, no prime
		jmp finito

prime:	
		mov rax,0x1		;return 1 if prime
		jmp finito 

finito:	
		mov rbx,r9		;restore rbx since we used it
		ret			;return to caller

