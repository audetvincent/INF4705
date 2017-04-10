CC=g++
CFLAGS=-I.
DEPS = Solution.h Exemplaire.h
OBJ = tp3.o Solution.o Exemplaire.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

tp3: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o tp3 
