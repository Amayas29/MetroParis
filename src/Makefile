FLAGS=-Wall -g
CC=gcc
EXEC=metrosParis

all: $(EXEC)

%.o : %.c
	$(CC) $(FLAGS) -c $^

metrosParis: *.o
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm *.o $(EXEC)