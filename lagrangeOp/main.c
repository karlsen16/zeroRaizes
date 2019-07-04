#include <stdio.h>
#include <math.h>
#define TAM 10
#define CASAS 10

typedef struct lagrange {
  double X[TAM];
  double Y[TAM];
  double x;
}Lagrange;

void preencher (Lagrange *L);
double formaLagrange (Lagrange *L, int indice);
void calcular (Lagrange *L);

int main () {
  Lagrange L;
  preencher(&L);
  calcular(&L);
  return 0;
}

void preencher (Lagrange *L) {
  int i;
  printf("\nInforme o valor buscado:\n");
  scanf("%lf", &L->x);
  printf("\nInforme os x:\n");
  for(i = 0; i < TAM; i++)
    scanf("%lf", &L->X[i]);
  printf("\nInforme os y:\n");
  for(i = 0; i < TAM; i++)
    scanf("%lf", &L->Y[i]);
}

double formaLagrange (Lagrange *L, int indice) {
  int i;
  double n = 1;
  for(i = 0; i < TAM; i++)
    if(i != indice)
      n *= (L->x-L->X[i])/(L->X[indice]-L->X[i]);
  return n;
}

void calcular (Lagrange *L) {
  double n = 0;
  int i;
  for(i = 0; i < TAM; i++)
    n += (L->Y[i]*formaLagrange(L, i));
  printf("\nResultado: %+.*lf.\n\n", CASAS, n);
}
