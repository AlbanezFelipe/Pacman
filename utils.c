#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Generate a random number from nr_min to nr_max
int randomNumber(int min, int max)
{
    // Initialize the random number generator with the current time
    // be sure that it is initialized only once
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }
    // generate the random number
    return rand() % max + min;
}
