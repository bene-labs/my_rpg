#include "../include/rpg.h"

int get_random_int_within_range(int min, int max)
{
    int result = 0;

    search_for_seed();
    result = (int) rand();
    if (result < 0 && min >= 0) result *= -1;
    result %= (max + 1 - min) + min;
    return (result);
}

int set_seed_if_file_is_valid(FILE *file)
{
    unsigned int  seed;

    if (!file)
        return (-1);
    if (fread(&seed, sizeof seed, 1, file) == 1) {
        fclose(file);
        srand(seed);
        return (0);
    }
    fclose(file);
    return (-1);
}

int search_for_seed(void)
{
    if (!set_seed_if_file_is_valid(fopen("/dev/urandom", "r")))
        return (0);
    if (!set_seed_if_file_is_valid(fopen("/dev/arandom", "r")))
        return (0);
    if (!set_seed_if_file_is_valid(fopen("/dev/random", "r")))
        return (0);
    return (-1);
}