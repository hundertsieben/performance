.PHONY: clean

all: pi pi_wtime

pi: pi.c
	$(CXX) pi.c -g $(CXXFLAGS) -o pi -fopenmp

pi_wtime:
	$(CXX) pi_wtime.c $(CXXFLAGS) -o pi_wtime -fopenmp

clean:
	rm pi pi_wtime
