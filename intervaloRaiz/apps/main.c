#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct intervalo{
    double a;           //limite inferior do intervalo
    double b;           //limite superior do intervalo
}Intervalo;

double funcao(double n);
Intervalo preencheIe();
void isolarRaiz(Intervalo *ie);

int main(){
    Intervalo ie = preencheIe();
    isolarRaiz(&ie);

    return 0;
}

double funcao(double n){
    return (pow(M_E,-pow(n,2))-cos(n));
}

Intervalo preencheIe(){
    Intervalo ie;
    printf("Digite o intervalo inicial:\n");
    scanf("%lf %lf", &ie.a, &ie.b);
    return ie;
}

void isolarRaiz(Intervalo *ie){
    double p = 0.01, i;
    int cont = 0;

    for(i = ie->a; i < ie->b; i+=p)
        if(ceil(funcao(i)*funcao(i+p)) == 0){
            cont++;
            printf("\n%2d# Raiz em: [%2.lf,%2.lf]", cont, floor(i), ceil(i+p));
        }
    printf("\n\n");
}
