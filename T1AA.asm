global f_vaciaE
global f_estandarE
global f_antiguaE

section .text

f_vaciaE:
	xor eax,eax		; deja en cero eax
	ret
	
f_estandarE:
	mov eax, edi	; edi = A, esi = B
	mul esi			; multiplica A por B
	ret
	
f_antiguaE:
	mov edx, edi	; edx = A
	mov ebx, esi	; ebx = B
	xor eax, eax	; eax = P
	
	BNoEsCero:		; mientras B no sea cero
	
	cmp ebx, 0
	je	BEsCero		; si B es 0 sale del while
	
		test ebx, 1	; Test hace un and con edx con 1
		jnz	esImpar	; Si es impar va a quedar prendido el bit 1
		jmp esPar
		
		esImpar:
			add eax, edx	; P = P + A
		esPar:
			add edx, edx	; A = A + A
			shr ebx, 1		; B = B/2
			
		jmp BNoEsCero
	
	BEsCero:
	ret

