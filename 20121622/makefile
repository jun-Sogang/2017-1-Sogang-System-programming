OBJECTS = 20121622.o function.o datastructures.o memory.o
cc=gcc
20121622.out: $(OBJECTS)
		$(cc) -Wall -o 20121622.out $(OBJECTS)

20121622.o: header.h datastructures.h memory.h 20121622.c
		$(cc) -Wall -c 20121622.c

function.o: header.h function.c
		$(cc) -Wall -c function.c

datastructures.o: datastructures.h datastructures.c
		$(cc) -Wall -c datastructures.c

memory.o: memory.h memory.c
				$(cc) -Wall -c memory.c

clean:
	rm -f $(OBJECTS)
	@echo "Clean Done"
