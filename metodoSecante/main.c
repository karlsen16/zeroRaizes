#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct intervalo{
    double a;           //limite inferior do intervalo
    double b;           //limite superior do intervalo
    double erro;
    double x0;          //flag, x0 e x1 sao pra controle de uso customizado dos valores iniciais
    double x1;
    int it_Max;
    int valo;           //intervalo que cont�m uma ra�z isolado a ser usado
    int r;              //indica que j� est� fazendo repeticoes e pula os preenchimentos iniciais
    int flag;
}Intervalo;

double funcao(double n);
double funcaoS(double n, double n2);
Intervalo preencheIe();
void pontoInicial(Intervalo *ie);
void atualizaIntervalo(Intervalo *ie, double a, double b);
void isolarRaiz(Intervalo *ie);
void iteracoes_Max(Intervalo *ie);
void imprimir(Intervalo *ie, double n);
double secante(Intervalo *ie, double n, double n2);

int main(){
    int retry = 1;
    Intervalo ie = preencheIe();
    pontoInicial(&ie);
    while(retry == 1){
        printf("\n\nDeseja calcular novamente com um novo it_MAX?\n\n### 0: Nao, terminar programa\n### 1: Sim, irei informar o novo it_MAX\n\n");
        scanf("%d", &retry);
        if(retry == 1){
            iteracoes_Max(&ie);
            ie.r = 1;                   //indica que já está fazendo repeticoes e pula os preenchimentos iniciais
            pontoInicial(&ie);
        }
    }
    return 0;
}

double funcao(double n){
    return (exp(-pow(n,2))-cos(n));
}

double funcaoS(double n, double n2){
    if((funcao(n)-funcao(n2)) == 0)
        return n;
    else
        return ((n2*funcao(n)-n*funcao(n2))/(funcao(n)-funcao(n2)));
}

Intervalo preencheIe(){
    Intervalo ie;
    int r;

    printf("Digite o intervalo inicial:\n");
    scanf("%lf %lf", &ie.a, &ie.b);
    printf("\nDigite o erro:\n");
    scanf("%d", &r);
    ie.erro = pow(10, -r);
    ie.valo = -1;
    isolarRaiz(&ie);
    printf("\n\nDigite o intervalo isolado escolhido:\n");
    scanf("%d", &ie.valo);
    isolarRaiz(&ie);
    ie.r = 0;
    iteracoes_Max(&ie);
    return ie;
}

void pontoInicial(Intervalo *ie){
    double n;
    if(ie->r == 0){
      printf("\nDeseja escolher os x(s) iniciais?\n\n### 0: Nao, deixar o programar escolher os mais adequados\n### 2: Sim, digitarei o x0 e x1\n\n");
      scanf("%d", &ie->flag);
      if(ie->flag != 0){
        printf("\nDigite x0 e x1:\n");
        scanf("%lf %lf", &ie->x0, &ie->x1);
      }
    }
    if(ie->flag == 0)
      n = secante(ie, ie->b, ie->a);
    else
      n = secante(ie, ie->x1, ie->x0);
    imprimir(ie, n);
}

void atualizaIntervalo(Intervalo *ie, double a, double b){
    ie->a = a;
    ie->b = b;
}

void iteracoes_Max(Intervalo *ie){
    printf("\nInforme ITMAX:\n");
    scanf("%d", &ie->it_Max);
}

void imprimir(Intervalo *ie, double n){
    printf("\n\nMetodo da Secante: %2.10lf\n\n", n);
}

void isolarRaiz(Intervalo *ie){
    double p = 0.01, i;
    int cont = 0;

    for(i = ie->a; i < ie->b; i+=p)
        if(ceil(funcao(i)*funcao(i+p)) == 0){
            cont++;
            if(ie->valo == -1)
                printf("\n%2d# Raiz em: [%2.lf,%2.lf]", cont, floor(i), ceil(i+p));

            if(ie->valo != -1 && cont == ie->valo){
                atualizaIntervalo(ie, floor(i), ceil(i+p));
                printf("\n### O intervalo escolhido foi: [%2.lf,%2.lf]###\n", ie->a, ie->b);
                break;
            }
        }
}

double secante(Intervalo *ie, double n, double n2){
    if(ie->it_Max >= 1){
        double p = funcaoS(n, n2);
        ie->it_Max--;
        printf("\n |p(x~n+1)- p(x~n)|: %2.10lf\n |p(x~n+1)|:         %2.10lf\n", fabs(p-n), fabs(funcao(p)));
        if((fabs(p-n) > ie->erro) && (fabs(funcao(n)) > ie->erro))
            n = secante(ie, p, n);
        else
            n = p;
    }
    return n;
}
