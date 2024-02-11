all:help.out strlength.out strconcat.out strcompare.out

help.out:help.c
	gcc help.c -o help.out
	./help.out

strlength.out:strlength.c mystrings.h mystrings.o
	gcc strlength.c mystrings.o -o strlength.out
	./strlength.out
	
strconcat.out:strconcat.c mystrings.h mystrings.o
	gcc strconcat.c mystrings.o -o strconcat.out
	./strconcat.out

strcompare.out:strcompare.c mystrings.h mystrings.o
	gcc strcompare.c mystrings.o -o strcompare.out
	./strcompare.out

mystrings.o:mystrings.c mystrings.h
	gcc -c mystrings.c -o mystrings.o

clean:
	rm -f *.out *.o