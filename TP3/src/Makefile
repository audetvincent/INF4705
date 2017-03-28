CC=g++
CFLAGS=-I.
DEPS = Solution.h Probleme.h
OBJ = tp3.o Solution.o Probleme.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

tp3: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o tp3 
