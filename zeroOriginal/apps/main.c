#include "raizes.h"

int main(){
    int retry = 1;
    Intervalo ie = preencheIe();
    pontoInicial(&ie);
    if(ie.op == 0)
        retry = 0;
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
