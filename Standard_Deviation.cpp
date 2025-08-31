// Taller 1 - Estructura de Datos - Punto 3: Desviación Estándar

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
    int n;
    // lee mientras haya un entero positivo
    while (scanf("%d", &n) == 1 && n > 0) {
        if (n <= 1) {
            // para n = 1 o menos dejamos 0 (no esta definida para n=1)
            printf("0.000000\n");
            continue;
        }
            long double nn = (long double)n;
            // desviacion estandar: sqrt(n*(n+1)/3)
            long double sd = sqrtl( nn * (nn + 1.0) / 3.0);
            printf("%.6Lf\n", sd);
    }
    return 0;
}
