#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct intervalo {
  double a;
  double b;
  double passo;
}Intervalo;

typedef struct entrada {
  double erro;
  int itMax;
  int intervalo;
  struct intervalo I;
}Entrada;

typedef struct printer {
  int casas;
  int parteDecimal;
}Printer;

double funcao (double x);
double funcaoS (double x, double x0);
void atualizaIntervalo (Intervalo *I, double a, double b);
Entrada preencher ();
void pontoInicial (Entrada *E);
void isolarRaiz (Entrada *E);
Printer arrumaPrint (double a, double passo);
double secante (Entrada *E, double x, double x0);

int main () {
  Entrada E = preencher();
  pontoInicial(&E);
  return 0;
}

double funcao (double x) {
  return (exp(-pow(x,2))-cos(x));
}

double funcaoS (double x, double x0) {
  if((funcao(x)-funcao(x0)) == 0)
    return x;
  else
    return ((x0*funcao(x)-x*funcao(x0))/(funcao(x)-funcao(x0)));
}

void atualizaIntervalo (Intervalo *I, double a, double b) {
  I->a = a;
  I->b = b;
}

Entrada preencher () {
  Entrada E;
  int r;
  double p;
  printf("Digite o intervalo inicial:\n");
  scanf("%lf %lf", &E.I.a, &E.I.b);
  printf("\nDigite o erro:\n");
  scanf("%d", &r);
  E.erro = pow(10, -r);
  printf("\nDigite o passo:\n");
  scanf("%lf", &p);
  E.I.passo = p;
  E.intervalo = -1;
  isolarRaiz(&E);
  printf("\nInforme ITMAX:\n");
  scanf("%d", &E.itMax);
  return E;
}

void pontoInicial (Entrada *E) {
  double x, x1;
  int flag;
  printf("\nDeseja escolher os x(s) iniciais?\n\n### 0: Nao, deixar o programar escolher os mais adequados\n### 1: Sim, digitarei o x0 e x1\n\n");
  scanf("%d", &flag);
  if(flag != 0) {
    printf("\nDigite x0 e x1:\n");
    scanf("%lf %lf", &x, &x1);
  }
  if(flag == 0)
    x = secante(E, E->I.b, E->I.a);
  else
    x = secante(E, x1, x);
  printf("\n\nDigite a quantidade de casas decimais na resposta:\n");
  scanf("%d", &flag);
  Printer A = arrumaPrint(x, pow(10, -flag));
  printf("\n\nMetodo da Secante: %+*.*lf\n\n", A.casas, A.parteDecimal, x);
}

void isolarRaiz (Entrada *E) {
  double i;
  int cont = 0;
  for(i = E->I.a; i < E->I.b; i+=E->I.passo)
    if(funcao(i)*funcao(i+E->I.passo) <= 0) {
      cont++;
      if(E->intervalo == -1 || E->intervalo == cont) {
        Printer A = arrumaPrint(i, E->I.passo);
        Printer B = arrumaPrint(i+E->I.passo, E->I.passo);
        if(E->intervalo == -1) {
          if(funcao(i)*funcao(i+E->I.passo) < 0)
            printf("\n%2d# Raiz em: [%+*.*lf, %+*.*lf]", cont, A.casas, A.parteDecimal, i, B.casas, B.parteDecimal, i+E->I.passo);
          else
            if(funcao(i+E->I.passo) == 0)
              printf("\n%2d# Encontrada uma raiz em x = %+*.*lf!", cont, B.casas, B.parteDecimal, i+E->I.passo);
            else
              printf("\n%2d# Encontrada uma raiz em x = %+*.*lf!", cont, A.casas, A.parteDecimal, i);
        }
        else if(E->intervalo == cont) {
          atualizaIntervalo(&(E->I), i, i+E->I.passo);
          printf("\n### O intervalo escolhido foi: [%+*.*lf, %+*.*lf]###\n",A.casas, A.parteDecimal, i, B.casas, B.parteDecimal, i+E->I.passo);
          break;
        }
      }
      if(funcao(i)*funcao(i+E->I.passo) == 0)
        i+=E->I.passo;
    }
  if(E->intervalo == -1 && cont != 0) {
    printf("\n\nDigite o intervalo isolado escolhido:\n");
    scanf("%d", &E->intervalo);
    isolarRaiz(E);
  }
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

double secante (Entrada *E, double x, double x0) {
  if(E->itMax >= 1) {
    double p = funcaoS(x, x0);
    E->itMax--;
    printf("\n |p(x:n+1)-p(x:n)|: %2.10lf", fabs(p-x));
    if(fabs(p-x) > E->erro)
      x = secante(E, p, x);
    else
      x = p;
  }
  return x;
}
