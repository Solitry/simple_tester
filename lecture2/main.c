#include <stdio.h>


int main() {
    int t;
    printf("Enter value for nmax: ");
    scanf("%d", &t);

    int max_cycle_seed = 0, max_cycle_len = -1, max_cycle_max_value = 0;

    for (int m = 1; m <= t; ++m) {
        int n = m, cycle_len = 0, max_value = m;

        while (n > 1) {
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }

            if (n > max_value) {
                max_value = n;
            }

            ++cycle_len;
        }

        if (cycle_len > max_cycle_len) {
            max_cycle_len = cycle_len;
            max_cycle_max_value = max_value;
            max_cycle_seed = m;
        }
    }

    printf("start = %7d, cycles = %6d, max = %9d\n", max_cycle_seed, max_cycle_len, max_cycle_max_value);
    
    return 0;
}