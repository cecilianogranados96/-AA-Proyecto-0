cli_exec:
	nasm -f elf64 T1AA.asm && gcc -Wall T1AA.c T1AA.o

clean:
	rm -rf a.out