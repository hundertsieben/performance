all: pi pi_wtime

pi: 
	$(CC) pi.c $(CFLAGS) -o pi -fopenmp

pi_wtime:
	$(CC) pi_wtime.c $(CFLAGS) -o pi_wtime -fopenmp

clean:
	rm pi pi_wtime
