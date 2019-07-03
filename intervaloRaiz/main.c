#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct intervalo {
  double a;
  double b;
  double passo;
}Intervalo;

typedef struct printer {
  int casas;
  int parteDecimal;
}Printer;

double funcao (double x);
Intervalo preencher ();
void isolarRaiz (Intervalo *I);
Printer arrumaPrint (double a, double passo);

int main () {
  Intervalo I = preencher();
  isolarRaiz(&I);
  return 0;
}

double funcao (double x) {
  return (sqrt(x)-5*exp(-x));
}

Intervalo preencher () {
  Intervalo I;
  printf("Digite o intervalo inicial:\n");
  scanf("%lf %lf", &I.a, &I.b);
  printf("Digite o passo:\n");
  scanf("%lf", &I.passo);
  return I;
}

void isolarRaiz (Intervalo *I) {
  double i;
  int cont = 0;
  for(i = I->a; i < I->b; i+=I->passo)
    if(funcao(i)*funcao(i+I->passo) <= 0) {
      cont++;
      Printer A = arrumaPrint(i, I->passo);
      Printer B = arrumaPrint(i+I->passo, I->passo);
      if(funcao(i)*funcao(i+I->passo) < 0)
        printf("\n%2d# Raiz em: [%+*.*lf, %+*.*lf]", cont, A.casas, A.parteDecimal, i, B.casas, B.parteDecimal, i+I->passo);
      else {
        if(funcao(i+I->passo) == 0)
          printf("\n%2d# Encontrada uma raiz em x = %+*.*lf!", cont, B.casas, B.parteDecimal, i+I->passo);
        else
          printf("\n%2d# Encontrada uma raiz em x = %+*.*lf!", cont, A.casas, A.parteDecimal, i);
        i+=I->passo;
      }
    }
  printf("\n\n");
}

Printer arrumaPrint (double a, double passo) {
  Printer novo;
  novo.casas = 0;
  novo.parteDecimal = 0;
  a = fabs(a);
  int inteiro;
  inteiro = (int) a;
  while(inteiro > 0) {
    inteiro /= 10;
    novo.casas++;
  }
  if(novo.casas == 0)
    novo.casas++;
  do {
    novo.parteDecimal++;
    passo *= 10;
    inteiro = (int) passo;
  }while(fabs(passo-inteiro) != 0);
  novo.casas += novo.parteDecimal+1;
  return novo;
}
