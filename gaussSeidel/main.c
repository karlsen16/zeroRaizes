#include <stdio.h>
#include <math.h>
#define TAM 4
#define Z 3

typedef struct seidel {
  double X[2][TAM];
  double B[TAM];
  double M[TAM][TAM];
  double erro;
  int it;
}Seidel;

void preencher (Seidel *S);
double gaussSeidel (Seidel *S);
void imprimir (Seidel *S);
void imprimirEspacos (int n);

int main () {
  Seidel S;
  preencher(&S);

  imprimir(&S);
  return 0;
}

void preencher (Seidel *S) {
  int i, j, flag = 0;
  printf("\nDeseja informar x:0 (%dx1)?\n", TAM);
  scanf("%d", &flag);
  printf("\nInforme os dados:\n");
  for(i = 0; i < TAM; i++) {
    for(j = 0; j < TAM; j++)
      scanf(" %lf", &(S->M[i][j]));
    if(flag != 0)
      scanf(" %lf", &(S->X[0][i]));
    else
      S->X[0][i] = 0;
    scanf(" %lf", &(S->B[i]));
  }
  printf("\nInforme o erro:\n");
  scanf("%lf", &S->erro);
  S->erro = pow(10,-(S->erro));
  S->it = 0;
}

double gaussSeidel (Seidel *S) {
  int i, j, control;
  control = S->it%2;
  for(i = 0; i < TAM; i++) {
    S->X[control][i] = S->B[i];
    for(j = 0; j < TAM; j++) {
      if(i != j) {
        if(i <= )
        S->X[control][i] += (S->M[i][j]*S->X[!control][j])
      }

  }
}

void imprimir (Seidel *S) {
  int i, j, flag;
  printf("\nDeseja quantas casas decimais?\n");
  scanf("%d", &flag);
  printf("\n\n");
  imprimirEspacos(Z);
  printf("M");
  imprimirEspacos(TAM*(Z+2+flag)+1);
  printf("X");
  imprimirEspacos(flag+Z+1);
  printf("B\n");
  for(i = 0; i < TAM; i++) {
    printf("|");
    for(j = 0; j < TAM; j++)
      printf("%+*.*lf ", Z+flag+1, flag, S->M[i][j]);
    printf("|%+*.*lf|", Z+flag+1, flag, S->X[0][i]);
    printf("%+*.*lf|", Z+flag+1, flag, S->B[i]);
    printf("\n");
  }
  printf("\n");
}

void imprimirEspacos (int n) {
  int i;
  for(i = 0; i < n; i++)
    printf(" ");
}
