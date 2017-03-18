OBJECTS = 20121622.o function.o linkedlist.o dump.o
cc=gcc
20121622.out: $(OBJECTS)
		$(cc) -o 20121622.out $(OBJECTS)

20121622.o: header.h linkedlist.h dump.h 20121622.c
		$(cc) -Wall -c 20121622.c

function.o: header.h function.c
		$(cc) -c function.c

linkedlist.o: linkedlist.h linkedlist.c
		$(cc) -c linkedlist.c

dump.o: dump.h dump.c
				$(cc) -c dump.c

clean:
	rm -f $(OBJECTS)
	@echo "Clean Done"
