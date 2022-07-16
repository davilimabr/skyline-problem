#include<stdio.h>
#include<stdlib.h>

bool ComecoOculto(int predio1[3], int predio2[3]){
    return (predio1[0] >= predio2[0] && predio1[0] <= predio2[1]) && predio1[2] <= predio2[2];
}

bool FimOculto(int predio1[3], int predio2[3]){
    return (predio1[1] >= predio2[0] && predio1[1] <= predio2[1]) && predio1[2] <= predio2[2];
}

bool PredioOculto(int predio1[3], int predio2[3]){
    return (predio1[0] >= predio2[0] && predio1[1] <= predio2[1]) && predio1[2] <= predio2[2];
}

bool PontoExiste(int pontos[][2], int qtd, int x, int y){
    for(int i = 0; i < qtd; i++)
        if(pontos[i][0] == x && pontos[i][1] == y)
            return true;
    
    return false;
}

bool PrediosIguais(int predio1[3], int predio2[3]){
    return predio1[0] == predio2[0] && predio1[1] == predio2[1] && predio1[2] == predio2[2];  
}

int ObterAlturaPredioAbaixodoFim(int predios[][3], int qtd, int prediox[3]){
    int maior_altura = 0; 
    for(int i = 0; i < qtd; i++)
        if(!FimOculto(predios[i], prediox)                            && 
        !PrediosIguais(predios[i], prediox)                           &&
        predios[i][2] < prediox[2]                                    &&
        predios[i][2] > maior_altura                                  &&
        (prediox[1] >= predios[i][0] && prediox[1] <= predios[i][1]))
            maior_altura = predios[i][2];

    return maior_altura;
}

int RetiraPrediosOcultos(int predios[][3], int qtd, int resultado[][3]){
    int r = 0;
    for(int i = 0; i < qtd; i++){
        bool oculto = false;
        
        for(int j = 0; j < qtd; j++)
            if(PredioOculto(predios[i], predios[j]) && j != i){
                oculto = true;
                break;
            }

        if(!oculto){
            for(int k = 0; k < 3; k++)
                resultado[r][k] = predios[i][k];

            r++;
        }
    }
    return r;
}

void OrdenaPontosCrescentePorX(int pontos[][2], int qtd){
    for(int i = 0; i < qtd-1;)
        if(pontos[i][0] > pontos[i+1][0]){
           int temp = pontos[i][0]; 
           pontos[i][0] = pontos[i+1][0];
           pontos[i+1][0] = temp;

           temp = pontos[i][1]; 
           pontos[i][1] = pontos[i+1][1];
           pontos[i+1][1] = temp;
        }
        else i++;
}

int ObterPontosSkyline(int predios[][3], int qtd_predio, int pontos[][2]){
    int p = 0;
    int predios_aux[qtd_predio][3];

    qtd_predio = RetiraPrediosOcultos(predios, qtd_predio, predios_aux);

    for(int i = 0; i < qtd_predio; i++){
        bool comeco_oculto = false;
        bool fim_oculto = false;

        for(int j = 0; j < qtd_predio; j++){
            if(ComecoOculto(predios_aux[i], predios_aux[j]) && j != i)
                comeco_oculto = true;

            if(FimOculto(predios_aux[i], predios_aux[j]) && j != i)
                fim_oculto = true;
        }
        if(!comeco_oculto){
            pontos[p][0] = predios_aux[i][0];
            pontos[p][1] = predios_aux[i][2];
            p++;
        }
        if(!fim_oculto){
            int p_altura = ObterAlturaPredioAbaixodoFim(predios_aux, qtd_predio, predios[i]);

            if(p_altura != 0 || !PontoExiste(pontos, p, predios_aux[i][2], 0)){
                pontos[p][0] = predios_aux[i][1];
                pontos[p][1] = p_altura;
                p++;
            }
        }
    }
    if(p > 2)
        OrdenaPontosCrescentePorX(pontos, p);

    return p;
}

void lerPredios(int predios[][3], int qtd){
    int ult_comeco = 0;

    for(int i = 0; i < qtd;){
        printf("Predio %d\n", i+1);
        puts("digite o valor de x1, correspondente ao comeco do predio");
        scanf("%d", &predios[i][0]);

        puts("digite o valor de x2, correspondente ao fim do predio");
        scanf("%d", &predios[i][1]);

        puts("digite o valor de y, correspondente a altura do predio");
        scanf("%d", &predios[i][2]);

        if(predios[i][0] >= predios[i][1] || predios[i][0] < ult_comeco || predios[i][2] <= 0 || predios[i][0] < 0 || predios[i][1] < 0){
            puts("dados referentes ao comeco e fim invalidos");
            system("pause");
        }
        else{
            ult_comeco = predios[i][0];
            i++;
        } 
        puts("\n");
    }
}

void ImprimirPontos(int pontos[][2], int qtd){
    for(int i = 0; i < qtd; i++)
        printf("%d - %d \n", pontos[i][0], pontos[i][1]);
}

int main(void){
    int qtd_predios;

    puts("Digite a quantidade e predios");
    scanf("%d", &qtd_predios);

    system("cls");

    int predios[qtd_predios][3];
    lerPredios(predios, qtd_predios);

    int pontos[qtd_predios * 2][2];
    int qtdp = ObterPontosSkyline(predios, qtd_predios, pontos);
    ImprimirPontos(pontos, qtdp);
}