#include <stdio.h>
#include <stdlib.h>

int doralaExploradora() {
    long long x = 0, y = 0;
    
    while (1) {
     
        scanf("%lld %lld", &x, &y);

        long long stepstaken = 0;
    
        if (x == 0 && y == 0) {
            break;  
        }
        
        long long diagonal = x + y - 1;
        long long itistriangular = (diagonal - 1) * diagonal / 2;
        
        if (diagonal % 2 == 0) {
            stepstaken = itistriangular + x;
        } else {
            stepstaken = itistriangular + y;
        }

        printf("%lld\n", stepstaken);
        }  
    
    return 0;  
}

int main(void) {
    doralaExploradora();
    return 0;
}
