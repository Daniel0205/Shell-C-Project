ejecutar: clean
	./shell
clean: shell
	rm -f  *.o *.a
shell: libfunShell.a
	gcc -L. -o shell shell.c -lfunShell
libfunShell.a: funShell.o
	ar -cvq libfunShell.a funShell.o
funShell.o: 
	gcc -c funShell.c

	
