# include <stdio.h>
# include <time.h>

int main() {
    int r[2800 + 1];
    int i, k;
    int b, d;
    int c = 0;
    int start, end;
    int delta;


    start=clock();
    ///////////////////////////
    ////////BENCHMARK//////////
    # pragma omp parallel for
    for (i = 0; i < 2800; i++) {
        r[i] = 2000;
    }

    # pragma omp for ordered schedule(dynamic)
    for (k = 2800; k > 0; k -= 14) {
        d = 0;

        i = k;
        for (;;) {
            d += r[i] * 10000;
            b = 2 * i - 1;

            r[i] = d % b;
            d /= b;
            i--;
            if (i == 0) break;
            d *= i;
        }

	# pragma omp ordered
        printf("%.4d", c + d / 10000);
        c = d % 10000;
    }
    ////////////////////////////
    end=clock();
    

    printf("\n\n");
    delta = end - start;
    printf("execution time in seconds: %d", delta);
    printf("\n\n");
    return 0;
}


