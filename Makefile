#-*-MakeFile-*-

#target: dependencias
#	accion (comando terminal)

all: Banco

Banco: main.o hash.o lista.o pila.o interfaz.o
	gcc main.o hash.o lista.o pila.o interfaz.o -o Banco

hash.o: hash.c lista.h pila.h interfaz.h
	gcc -c hash.c

lista.o: lista.c hash.h
	gcc -c lista.c

pila.o: pila.c hash.h
	gcc -c pila.c

interfaz.o: interfaz.c hash.h
	gcc -c interfaz.c

main.o: main.c hash.h lista.h pila.h interfaz.h
	gcc -c main.c


clean:
	rm -f *.o Banco
