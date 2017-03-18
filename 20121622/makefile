OBJECTS = 20121622.o function.o linkedlist.o memory.o
cc=gcc
20121622.out: $(OBJECTS)
		$(cc) -o 20121622.out $(OBJECTS)

20121622.o: header.h linkedlist.h memory.h 20121622.c
		$(cc) -Wall -c 20121622.c

function.o: header.h function.c
		$(cc) -c function.c

linkedlist.o: linkedlist.h linkedlist.c
		$(cc) -c linkedlist.c

memory.o: memory.h memory.c
				$(cc) -c memory.c

clean:
	rm -f $(OBJECTS)
	@echo "Clean Done"
