// Taller 2 - Estructura de Datos - Punto 1: Coffee

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAXT 500000
#define MAXIT 1000

double volumen_total(double r, double R, double H){
    const double pi = 3.141592653589793;
    return (pi * H * (R*R + R*r + r*r)) / 3.0;
}

double volumen_inferior(double x, double r, double R, double H){
    const double pi = 3.141592653589793;
    double rc = R+(r-R)*x/H;
    return (pi * x * (R*R + R*rc + rc*rc)) / 3.0;
}

double corte_altura(double r, double R, double H, double V){
    double inferior = 0.0;
    double superior = H;
    for(int iter = 0; iter < MAXIT; iter++){
        double medio = (inferior + superior) / 2.0;
        double Vmedio = volumen_inferior(medio, r, R, H);
        if(Vmedio < V){
            inferior = medio;
        } else {
            superior = medio;
        }
    }
    return (inferior + superior) / 2.0;
}

int main(void) {
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        double r, R, H;
        scanf("%lf %lf %lf", &r, &R, &H);
        double Vtotal = volumen_total(r, R, H);
        double h = H - corte_altura(r, R, H, Vtotal / 2.0); // Buscar altura para mitad de volumen
        printf("%.9lf\n", h);
    }
    return 0;
}
