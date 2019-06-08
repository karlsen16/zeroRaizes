#ifndef __RAIZES_H
#define __RAIZES_H
#include <stdio.h>
#include <math.h>


typedef struct intervalo{
    double a;           //limite inferior do intervalo
    double b;           //limite superior do intervalo
    double m;           //valor m�dio dentro do intervalo completo
    double erro;
    double x0;          //flag, x0 e x1 sao pra controle de uso customizado dos valores iniciais
    double x1;
    int it_Max;
    int valo;           //intervalo que cont�m uma ra�z isolado a ser usado
    int op;             //metodo escolhido
    int r;              //indica que j� est� fazendo repeticoes e pula os preenchimentos iniciais
    int flag;

}Intervalo;

double funcao(double n);
double funcaoPF(double n);
double derivada(double n);
double funcaoT(double n);
double funcaoS(double n, double n2);
Intervalo preencheIe();
void pontoInicial(Intervalo *ie);
void atualizaIntervalo(Intervalo *ie, double a, double b);
void iteracoes_Max(Intervalo *ie);
void imprimir(Intervalo *ie, double n);
void isolarRaiz(Intervalo *ie);
double bisseccao(Intervalo *ie);
double pontoFixo(Intervalo *ie, double n);
double tangente(Intervalo *ie, double n);
double secante(Intervalo *ie, double n, double n2);



#endif /* __RAIZES_H */
