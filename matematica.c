#include "matematica.h"

int funcion_interna();

double factorial(int n){
    double fact = 1.0;
    if(n < 0){
        return 0;
    }

    for(int i =1 ; i <= n ; i++) {
        printf("Paso %d: fact = %.0f\n", i, fact);
        fact *= i;
    }
    return fact;
}

int combinatorio (int n, int m) {
    return factorial(m) / (factorial(n)*factorial(m-n));
}

int funcion_interna() {
    return 0;
}
