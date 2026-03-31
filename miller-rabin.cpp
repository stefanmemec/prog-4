#include <stdlib.h>
#include <stdint.h>
#include "miller-rabin.h"

static int (*rand_func)(void) = rand;
static int rand_max = RAND_MAX;

static uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
    uint64_t result = 1;

    while (x > 0)
    {
        if (x % 2 == 1)
            result = (result * a) % n;

        a = (a * a) % n;
        x /= 2;
    }

    return result;
}

static uint64_t rand_between(uint64_t a, uint64_t b)
{
    uint64_t r = ((uint64_t)rand_func() << 32) | rand_func();
    return a + (uint64_t)((double)(b - a + 1) * r / (UINT64_MAX + 1.0));
}

bool isprime(uint64_t n, int k)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0)
        return false;

    uint64_t temp = n - 1;
    int s = 0;

    while (temp % 2 == 0)
    {
        temp /= 2;
        s++;
    }

    uint64_t d = temp;

    for (int i = 0; i < k; i++)
    {
        uint64_t a = rand_between(2, n - 2);
        uint64_t x = pow_mod(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool passed = false;

        for (int r = 1; r < s; r++)
        {
            x = pow_mod(x, 2, n);

            if (x == 1)
                return false;

            if (x == n - 1)
            {
                passed = true;
                break;
            }
        }

        if (!passed)
            return false;
    }

    return true;
}

void setrand(int (*pf)(void), const int rmax)
{
    if (pf != NULL)
    {
        rand_func = pf;
        rand_max = rmax;
    }
    else
    {
        rand_func = rand;
        rand_max = RAND_MAX;
    }
}