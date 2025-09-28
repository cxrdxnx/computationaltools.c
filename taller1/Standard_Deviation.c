
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
    int n;

    while (scanf("%d", &n) == 1 && n > 0) {
        
            long double nn = (long double)n;
    
            long double sd = sqrtl( nn * (nn + 1.0) / 3.0);
            printf("%.6Lf\n", sd);
    }
    return 0;
}
