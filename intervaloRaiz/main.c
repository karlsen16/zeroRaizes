#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct intervalo{
    double a;           //limite inferior do intervalo
    double b;           //limite superior do intervalo
    double passo;       //passo do intervalo e busca
}Intervalo;

typedef struct printer{
    int pU;             /*usada apenas para melhorar o print*/
    int pD;
}prT;

double funcao(double n);            //funcao utilizada
Intervalo preencheIe();             //recebe as informações
void isolarRaiz(Intervalo *ie);     //procura e imprime as raizes
prT rI (double a, double passo);    //apenas para o print, não intefere no cálculo

int main(){
    Intervalo ie = preencheIe();
    isolarRaiz(&ie);
    return 0;
}

double funcao(double n){
    return (sqrt(n)-5*exp(-n));
}

Intervalo preencheIe(){
    Intervalo ie;
    printf("Digite o intervalo inicial:\n");
    scanf("%lf %lf", &ie.a, &ie.b);
    printf("Digite o passo:\n");
    scanf("%lf", &ie.passo);
    return ie;
}

void isolarRaiz(Intervalo *ie){
    double i;
    int cont = 0;
    for(i = ie->a; i < ie->b; i+=ie->passo)
        if(funcao(i)*funcao(i+ie->passo) <= 0){
            cont++;
            prT aux1 = rI(i, ie->passo);
            prT aux2 = rI(i+ie->passo, ie->passo);
            if(funcao(i)*funcao(i+ie->passo) < 0)
                printf("\n%2d# Raiz em: [%+*.*lf, %+*.*lf]", cont, aux1.pU, aux1.pD, i, aux2.pU, aux2.pD, i+ie->passo);
            else{
                if(funcao(i+ie->passo) == 0)
                    printf("\n%2d# Encontrada uma raiz em x = %+*.*lf!", cont, aux2.pU, aux2.pD, i+ie->passo);
                else
                    printf("\n%2d# Encontrada uma raiz em x = %+*.*lf!", cont, aux1.pU, aux1.pD, i);
                i+=ie->passo;
            }
        }
    printf("\n\n");
}

prT rI (double a, double passo){
    prT neu;
    neu.pU = 0;
    neu.pD = 0;
    a = fabs(a);
    int nt;
    nt = (int) a;
    while(nt > 0){
        nt /= 10;
        neu.pU++;
    }
    if(neu.pU == 0)
        neu.pU++;
    do{
        neu.pD++;
        passo *= 10;
        nt = (int) passo;
    }while(fabs(passo-nt) != 0);
    neu.pU += neu.pD+1;
    return neu;
}
