#include <stdlib.h>
#include "raizes.h"


double funcao(double n){
    /*Fun��o principal usada para encontrar a ra�z
    para achar um certo valor de x -> transformar o problema em f(x) = 0
    M_E -> n�mero de euler
    M_PI -> n�mero pi
    */
    return (pow(M_E,-pow(n,2))-cos(n));
}

double funcaoPF(double n){
    /*Fun��o phi usada no m�todo do ponto fixo,
    verifica��o de converg�ncia n�o � feita pelo programa!*/
    return (cos(n)-pow(M_E,-pow(n,2))+n);
}

double derivada(double n){
    /*Fun��o de derivada para o m�todo das tangentes*/
    return (pow(M_E,-pow(n,2))*-2*n+sin(n));
}

double funcaoT(double n){
    if(derivada(n) == 0)
        return n;
    else
        return(n-(funcao(n)/derivada(n)));
}

double funcaoS(double n, double n2){
    /*n-> x atual
    n2-> x anterior
    */
    if((funcao(n)-funcao(n2)) == 0)
        return n;
    else
        return ((n2*funcao(n)-n*funcao(n2))/(funcao(n)-funcao(n2)));
}

Intervalo preencheIe(){
    /*Faz o preenchimento inicial de uma struct intervalo
    o erro deve ser o n�mero de casas decimais que devem ser
    id�nticas ao do valor exato procurado.
    p.e.: 5 -> 10^-5 -> as primeiras 5 casas decimais devem estar corretas
    Intervalo escolhido � definido entre 1 e n. Sendo n o n�mero
    de intervalos isolados com ra�z. Contando de A para B informados.
    */
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
    printf("\nDigite o metodo a ser usado:\n\n### 0: Bisseccao\n### 1: Ponto-fixo\n### 2: Tangente\n### 3: Secante\n\n");
    scanf("%d", &ie.op);
    ie.r = 0;
    iteracoes_Max(&ie);
    return ie;
}

void pontoInicial(Intervalo *ie){
    /*Menu de sele��o interno do m�todo a ser usado
    */
    double n;

    if(ie->op != 0){
        if(ie->r == 0){
            switch(ie->op){
                case 3:
                    printf("\nDeseja escolher os x(s) iniciais?\n\n### 0: Nao, deixar o programar escolher os mais adequados\n### 2: Sim, digitarei o x0 e x1\n\n");
                break;
                default:
                    printf("\nDeseja escolher o x inicial?\n\n### 0: Nao, deixar o programar escolher o mais adequado\n### 1: Sim, digitarei o x0\n\n");
                break;
            }
            scanf("%d", &ie->flag);
            switch(ie->flag){
                case 1:
                    printf("\nDigite x0:\n");
                    scanf("%lf", &ie->x0);
                break;
                case 2:
                    printf("\nDigite x0 e x1:\n");
                    scanf("%lf %lf", &ie->x0, &ie->x1);
                break;
            }
        }
    }
    switch(ie->op){
        case 0:
            n = bisseccao(ie);
        break;
        case 1:
            if(ie->flag == 0)
                if(ie->m > funcaoPF(ie->m)){
                    n = pontoFixo(ie, ie->a);
                }
                else if(ie->m < funcaoPF(ie->m)){
                    n = pontoFixo(ie, ie->b);
                }
                else
                    n = ie->m;
            else
                n = pontoFixo(ie, ie->x0);
        break;
        case 2:
            if(ie->flag == 0)
                if(funcaoT(ie->a) >= ie->a && funcaoT(ie->a) <= ie->b)
                    n = tangente(ie, ie->a);
                else
                    n = tangente(ie, ie->b);
            else
                n = tangente(ie, ie->x0);
        break;
        case 3:
            if(ie->flag == 0)
                n = secante(ie, ie->b, ie->a);
            else
                n = secante(ie, ie->x1, ie->x0);
        break;
        default:
            printf("### Opcao inv�lida!");
            exit(1);
    }
    imprimir(ie, n);
}

void atualizaIntervalo(Intervalo *ie, double a, double b){
    /*Fun��o para r�pida atualiza��o de A e B na struct Intervalo*/
    ie->a = a;
    ie->b = b;
    ie->m = (a+b)/2;
}

void iteracoes_Max(Intervalo *ie){
    /*Fun��o para determinar o n�mero de itera��es m�ximas*/
    if(ie->op == 0)
        ie->it_Max = (int)(ceil((log10(ie->b-ie->a)-log10(ie->erro))/log10(2)));
    else{
        printf("\nInforme ITMAX:\n");
        scanf("%d", &ie->it_Max);
    }
}

void imprimir(Intervalo *ie, double n){
    switch(ie->op){
        case 0:
            printf("\n\nMetodo da Bisseccao: %2.10lf\n\n", n);
        break;
        case 1:
            printf("\n\nMetodo da Ponto-fixo: %2.10lf\n\n", n);
        break;
        case 2:
            printf("\n\nMetodo da Tangente: %2.10lf\n\n", n);
        break;
        case 3:
            printf("\n\nMetodo da Secante: %2.10lf\n\n", n);
        break;
        default:
            printf("##Opcao inv�lida!");
            exit(1);
    }
}

void isolarRaiz(Intervalo *ie){
    /*Isola os intervalos encontrados com a ra�z da fun��o principal
    p -> � o passo a cada itera��o
    cont -> conta os intervalos isolados encontrados
    obs.: Todos os intervalos encontrados s�o printados e
    caso pelo menos um seja encontrado o intervalo utilizado ser� informado
    */
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

double bisseccao(Intervalo *ie){
    if((ie->it_Max > 1) && (funcao(ie->a)*funcao(ie->m) != 0)){
        if((funcao(ie->a)*funcao(ie->m)) < 0)
            atualizaIntervalo(ie, ie->a, ie->m);
        else
            atualizaIntervalo(ie, ie->m, ie->b);
        ie->it_Max--;
        return bisseccao(ie);
    }
    else
      if(!funcao(ie->a))
        return ie->a;
      else
        return ie->m;
}

double pontoFixo(Intervalo *ie, double n){
    double p = funcaoPF(n);
    if(p != n && ie->it_Max >= 1){
        ie->it_Max--;
        printf("\n |p(x~n)- p(x~n-1)|: %2.10lf\n |p(x~n)|:           %2.10lf\n", fabs(p-n), fabs(funcao(p)));
        if((fabs(p-n) > ie->erro) && (fabs(funcao(p)) > ie->erro))
            n = pontoFixo(ie, p);
        else
            n = p;
    }
    return n;
}

double tangente(Intervalo *ie, double n){
    double p = funcaoT(n);
    if(p != n && ie->it_Max >= 1){
        ie->it_Max--;
        printf("\n |p(x~n)- p(x~n-1)|: %2.10lf\n |p(x~n)|:           %2.10lf\n", fabs(p-n), fabs(funcao(p)));
        if((fabs(p-n) > ie->erro) && (fabs(funcao(p)) > ie->erro))
            n = tangente(ie, p);
        else
            n = p;
    }
    return n;
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
