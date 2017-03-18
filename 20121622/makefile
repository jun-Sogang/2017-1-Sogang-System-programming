OBJECTS = 20121622.o function.o linkedlist.o
cc=gcc
20121622.out: $(OBJECTS)
		$(cc) -o 20121622.out $(OBJECTS)

20121622.o: header.h linkedlist.h 20121622.c
		$(cc) -c 20121622.c

function.o: header.h function.c
		$(cc) -c function.c

linkedlist.o: linkedlist.h linkedlist.c
		$(cc) -c linkedlist.c


clean:
	rm -f $(OBJECTS)
	@echo "Clean Done"
