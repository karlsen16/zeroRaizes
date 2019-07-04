#include <stdio.h>
#include <math.h>
#define TAM 6
#define Z 4

typedef struct seidel {
  double X[2][TAM];
  double B[TAM];
  double M[TAM][TAM];
  double erro;
  int it;
}Seidel;

void preencher (Seidel *S);
void gaussSeidel (Seidel *S);
double retornaMaximo (double X[2][TAM], int control);
void imprimir (Seidel *S, int casas);
void imprimirEspacos (int n);

int main () {
  Seidel S;
  int casas, i;
  preencher(&S);
  printf("\nDeseja quantas casas decimais?\n");
  scanf("%d", &casas);
  imprimir(&S, casas);
  gaussSeidel(&S);
  imprimir(&S, casas);
  printf("\nSistema resolvido utilizando o metodo Gauss-Seidel.\nResultados:\n");
  printf("Iteracoes: %d.", S.it);
  printf("\n\n   Vetor X");
  for(i = 0; i < TAM; i++)
    printf("\n|%+*.*lf|", Z+casas+1, casas, S.X[(S.it)%2][i]);
  printf("\n\n");
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
    S->X[1][i] = 0;
    scanf(" %lf", &(S->B[i]));
  }
  printf("\nInforme o erro:\n");
  scanf("%lf", &S->erro);
  S->erro = pow(10,-(S->erro));
  S->it = 0;
}

void gaussSeidel (Seidel *S) {
  int i, j, control;
  S->it++;
  control = (S->it)%2;
  for(i = 0; i < TAM; i++) {
    S->X[control][i] = S->B[i];
    for(j = 0; j < TAM; j++) {
      if(i != j) {
        if(i > j)
          S->X[control][i] += -1*(S->M[i][j]*S->X[control][j]);
        else
          S->X[control][i] += -1*(S->M[i][j]*S->X[!control][j]);
      }
    }
    S->X[control][i] /= S->M[i][i];
  }
  if(retornaMaximo(S->X, control) > S->erro)
    gaussSeidel (S);
}

double retornaMaximo (double X[2][TAM], int control) {
  double maximo = 0;
  int i;
  for(i = 0; i < TAM; i++)
    if(fabs(X[control][i]-X[!control][i]) > maximo)
      maximo = fabs(X[control][i]-X[!control][i]);
  return maximo;
}

void imprimir (Seidel *S, int casas) {
  int i, j;
  printf("\n\n");
  imprimirEspacos(Z);
  printf("M");
  imprimirEspacos(TAM*(Z+2+casas)+1);
  printf("X");
  imprimirEspacos(casas+Z+1);
  printf("B\n");
  for(i = 0; i < TAM; i++) {
    printf("|");
    for(j = 0; j < TAM; j++)
      printf("%+*.*lf ", Z+casas+1, casas, S->M[i][j]);
    printf("|%+*.*lf|", Z+casas+1, casas, S->X[(S->it)%2][i]);
    printf("%+*.*lf|", Z+casas+1, casas, S->B[i]);
    printf("\n");
  }
  printf("\n");
}

void imprimirEspacos (int n) {
  int i;
  for(i = 0; i < n; i++)
    printf(" ");
}
