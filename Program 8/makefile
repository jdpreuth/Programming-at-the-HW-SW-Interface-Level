Crypto: Key.o Stats.o Crypto.o 
	gcc -g Crypto.o Key.o Stats.o -o Crypto

Key.o: Key.h Key.c Stats.h
	gcc -g -std=c99 -pedantic -Wall -Wextra -O1 -c Key.c

Stats.o: Stats.h Stats.c Key.h 
	gcc -g -std=c99 -pedantic -Wall -Wextra -O1 -c Stats.c

Crypto.o: Key.h Stats.h
	gcc -g -std=c99 -pedantic -Wall -Wextra -O1 -c Crypto.c

clean: 
	rm -f *.o