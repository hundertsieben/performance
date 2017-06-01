.PHONY: clean

all: pi pi_wtime

pi: pi.c
	$(CC) pi.c -g $(CFLAGS) -o pi -fopenmp

pi_wtime:
	$(CC) pi_wtime.c $(CFLAGS) -o pi_wtime -fopenmp

clean:
	rm pi pi_wtime
