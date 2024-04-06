#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

volatile int a[1024 * 4096] = {0};

int main(int argc, char *argv[])
{
    if (argc < 4) // Check for exactly 3 arguments
    {
        fprintf(stderr, "Usage: %s <PAGESIZE> <NUMPAGES> <TIMES>\n", argv[0]); // Error message to stderr
        exit(EXIT_FAILURE);   
    }
    
    // Get args from command line
    int PAGESIZE = atoi(argv[1]);
    int NUMPAGES = atoi(argv[2]);
    int times = atoi(argv[3]);
    int jump = PAGESIZE / sizeof(int);
    
    if (jump <= 0) {
        fprintf(stderr, "Invalid PAGESIZE provided.\n");
        exit(EXIT_FAILURE);
    }
    
    // Setup variables for time calculation
    struct timeval t1, t2;
    long double timecost;

    gettimeofday(&t1, NULL);

    for (size_t i = 0; i < times; i++)
    {
        for (size_t j = 0; j < NUMPAGES * jump; j += jump)
        {
            a[j]++;
        }
    }

    gettimeofday(&t2, NULL);

    // Calculate timecost in nanoseconds
    timecost = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + (t2.tv_usec - t1.tv_usec)) * 1000.0;
    timecost /= times;
    timecost /= NUMPAGES;

    printf("%.2Lf\n", timecost);

    return 0;
}

